import re
from pathlib import Path

KEYFRAME_FILE = "ae_keyframe.txt"
IMAGE_NAME_FILE = "image_name.txt"
OUTPUT_FILE = "output.txt"

SUPPORTED_TYPES = ["Position", "Rotation", "Scale"]
EPSILON = 0.000001


def is_number(text: str) -> bool:
    try:
        float(text)
        return True
    except ValueError:
        return False


def format_number(value: float) -> str:
    """
    C++ 숫자 리터럴 형태로 변환합니다.

    규칙:
    1.0      -> 1
    26.0     -> 26
    0.95     -> 0.95f
    -22.5    -> -22.5f
    41.875   -> 41.875f

    즉, 정수면 f 없음.
    실수면 f 붙임.
    """
    value = float(value)

    rounded_value = round(value, 6)

    nearest_int = round(rounded_value)
    if abs(rounded_value - nearest_int) < EPSILON:
        return str(int(nearest_int))

    text = f"{rounded_value:.6f}".rstrip("0").rstrip(".")
    return text + "f"


def get_transform_type_from_line(line: str):
    parts = re.split(r"\s+", line.strip())

    if len(parts) >= 2 and parts[0] == "Transform":
        if parts[1] in SUPPORTED_TYPES:
            return parts[1]

    return None


def parse_transform_blocks(text: str):
    blocks = []

    current_type = None
    current_keyframes = []

    lines = text.splitlines()

    def push_current_block():
        nonlocal current_type, current_keyframes

        if current_type is not None and len(current_keyframes) > 0:
            blocks.append({
                "type": current_type,
                "keyframes": current_keyframes
            })

        current_type = None
        current_keyframes = []

    for line in lines:
        stripped = line.strip()

        if not stripped:
            continue

        found_type = get_transform_type_from_line(stripped)

        if found_type is not None:
            push_current_block()
            current_type = found_type
            current_keyframes = []
            continue

        if current_type is None:
            continue

        parts = re.split(r"\s+", stripped)

        if len(parts) == 0:
            continue

        if not is_number(parts[0]):
            continue

        frame = float(parts[0])

        if current_type == "Rotation":
            if len(parts) < 2:
                continue

            value = float(parts[1])
            current_keyframes.append((frame, value))

        elif current_type in ["Position", "Scale"]:
            if len(parts) < 3:
                continue

            x = float(parts[1])
            y = float(parts[2])
            current_keyframes.append((frame, x, y))

    push_current_block()

    return blocks


def make_function_name(transform_type: str) -> str:
    if transform_type == "Position":
        return "PositionTo"

    if transform_type == "Rotation":
        return "RotationTo"

    if transform_type == "Scale":
        return "ScaleTo"

    raise ValueError("지원하지 않는 Transform 타입입니다.")


def values_are_same(a, b, transform_type: str) -> bool:
    if transform_type == "Rotation":
        return abs(a[1] - b[1]) < EPSILON

    return (
        abs(a[1] - b[1]) < EPSILON
        and abs(a[2] - b[2]) < EPSILON
    )


def convert_keyframe_block(transform_type: str, keyframes, image_name: str):
    result = []

    if len(keyframes) < 2:
        return result

    function_name = make_function_name(transform_type)

    if transform_type == "Position":
        base_x = keyframes[0][1]
        base_y = keyframes[0][2]

    for i in range(len(keyframes) - 1):
        current = keyframes[i]
        next_key = keyframes[i + 1]

        # 값이 변하지 않는 구간은 생략
        if values_are_same(current, next_key, transform_type):
            continue

        start_frame = current[0]
        duration = next_key[0] - current[0]

        start_frame_text = format_number(start_frame)
        duration_text = format_number(duration)

        if transform_type == "Rotation":
            next_value = next_key[1]
            value_text = format_number(next_value)

        elif transform_type == "Position":
            # 첫 번째 키프레임 값을 기준으로 한 변화량
            next_x = next_key[1] - base_x
            next_y = next_key[2] - base_y

            x_text = format_number(next_x)
            y_text = format_number(next_y)

            value_text = f"Vector2({x_text}, {y_text})"

        elif transform_type == "Scale":
            # After Effects Scale 값은 percent라서 100으로 나눔
            next_x = next_key[1] / 100
            next_y = next_key[2] / 100

            x_text = format_number(next_x)
            y_text = format_number(next_y)

            value_text = f"Vector2({x_text}, {y_text})"

        line = (
            f'\tclip.AddKeyFrame(clip.{function_name}'
            f'({start_frame_text}, L"{image_name}", {value_text}, {duration_text}, EaseType::EaseInOut));'
        )

        result.append(line)

    return result


def convert_all_blocks(blocks, image_name: str):
    result = []

    for index, block in enumerate(blocks):
        transform_type = block["type"]
        keyframes = block["keyframes"]

        converted_lines = convert_keyframe_block(transform_type, keyframes, image_name)

        if len(converted_lines) == 0:
            result.append(
                f"\t// {transform_type}: 변환할 키프레임이 없습니다. "
                f"모든 값이 동일하거나 키프레임이 부족합니다."
            )
        else:
            result.extend(converted_lines)

        if index != len(blocks) - 1:
            result.append("")

    return result


def main():
    keyframe_path = Path(KEYFRAME_FILE)
    image_name_path = Path(IMAGE_NAME_FILE)

    if not keyframe_path.exists():
        raise FileNotFoundError(f"{KEYFRAME_FILE} 파일을 찾을 수 없습니다.")

    if not image_name_path.exists():
        raise FileNotFoundError(f"{IMAGE_NAME_FILE} 파일을 찾을 수 없습니다.")

    keyframe_text = keyframe_path.read_text(encoding="utf-8")
    image_name = image_name_path.read_text(encoding="utf-8").strip()

    if not image_name:
        raise ValueError(f"{IMAGE_NAME_FILE} 안에 이미지 이름이 없습니다.")

    blocks = parse_transform_blocks(keyframe_text)

    if len(blocks) == 0:
        raise ValueError("Position, Rotation, Scale 키프레임 블록을 찾지 못했습니다.")

    result = convert_all_blocks(blocks, image_name)

    if len(result) == 0:
        output_text = "// 변환할 키프레임이 없습니다."
    else:
        output_text = "\n".join(result)

    Path(OUTPUT_FILE).write_text(output_text, encoding="utf-8")

    print(output_text)
    print()
    print(f"변환 완료: {OUTPUT_FILE} 파일에 저장되었습니다.")

    input("\n엔터를 누르면 종료합니다...")


if __name__ == "__main__":
    main()