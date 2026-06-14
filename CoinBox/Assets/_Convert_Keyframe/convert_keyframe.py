import re
from pathlib import Path

KEYFRAME_FILE = "ae_keyframe.txt"
IMAGE_NAME_FILE = "image_name.txt"
OUTPUT_FILE = "output.txt"


def format_number(value: float, add_f_for_float: bool = True) -> str:
    """
    C++ 코드에 넣을 숫자 형태로 변환
    1.0 -> 1
    0.95 -> 0.95f
    -22.5 -> -22.5f
    """
    if abs(value - int(value)) < 0.000001:
        return str(int(value))

    text = f"{value:.6f}".rstrip("0").rstrip(".")
    return text + "f" if add_f_for_float else text


def parse_transform_type(text: str) -> str:
    if "Transform\tPosition" in text:
        return "Position"
    if "Transform\tScale" in text:
        return "Scale"
    if "Transform\tRotation" in text:
        return "Rotation"

    raise ValueError("Position, Scale, Rotation 중 어떤 키프레임인지 찾지 못했습니다.")


def parse_keyframes(text: str, transform_type: str):
    keyframes = []

    lines = text.splitlines()

    for line in lines:
        line = line.strip()

        if not line:
            continue

        parts = re.split(r"\s+", line)

        # 첫 번째 값이 프레임 숫자인 줄만 처리
        if not parts[0].isdigit():
            continue

        frame = int(parts[0])

        if transform_type == "Rotation":
            value = float(parts[1])
            keyframes.append((frame, value))

        elif transform_type in ["Position", "Scale"]:
            x = float(parts[1])
            y = float(parts[2])
            keyframes.append((frame, x, y))

    return keyframes


def make_function_name(transform_type: str) -> str:
    if transform_type == "Position":
        return "MakePositionKeyFrame"
    if transform_type == "Scale":
        return "MakeScaleKeyFrame"
    if transform_type == "Rotation":
        return "MakeRotationKeyFrame"

    raise ValueError("지원하지 않는 Transform 타입입니다.")


def values_are_same(a, b, transform_type: str) -> bool:
    if transform_type == "Rotation":
        return abs(a[1] - b[1]) < 0.000001

    return abs(a[1] - b[1]) < 0.000001 and abs(a[2] - b[2]) < 0.000001


def convert_keyframes(keyframes, transform_type: str, image_name: str):
    result = []

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

        if transform_type == "Rotation":
            next_value = next_key[1]
            value_text = format_number(next_value)

        elif transform_type == "Position":
            next_x = next_key[1] - base_x
            next_y = next_key[2] - base_y

            x_text = format_number(next_x)
            y_text = format_number(next_y)

            value_text = f"Vector2f({x_text}, {y_text})"

        elif transform_type == "Scale":
            next_x = next_key[1] / 100
            next_y = next_key[2] / 100

            x_text = format_number(next_x)
            y_text = format_number(next_y)

            value_text = f"Vector2f({x_text}, {y_text})"

        line = (
            f'\tclip.AddKeyFrame(clip.{function_name}'
            f'({start_frame}, "{image_name}", {value_text}, {duration}, EaseType::EaseInOut));'
        )

        result.append(line)

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

    transform_type = parse_transform_type(keyframe_text)
    keyframes = parse_keyframes(keyframe_text, transform_type)

    if len(keyframes) < 2:
        raise ValueError("키프레임이 2개 이상 필요합니다.")

    result = convert_keyframes(keyframes, transform_type, image_name)
    output_text = "\n".join(result)

    Path(OUTPUT_FILE).write_text(output_text, encoding="utf-8")

    print(output_text)
    print()
    print(f"변환 완료: {OUTPUT_FILE} 파일에 저장되었습니다.")

    input("\n엔터를 누르면 종료합니다...")


if __name__ == "__main__":
    main()