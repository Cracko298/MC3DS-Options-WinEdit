import sys

def modify_file(file_path):
    target_bytes = bytes([0xD8, 0x05, 0x20, 0x20, 0x6D, 0x70])
    with open(file_path, 'rb') as file:
        content = file.read()

        if content.startswith(target_bytes):
            modified_content = content.replace(b'\x20', b'\x00')

            with open(file_path, 'wb') as modified_file:
                modified_file.write(modified_content)
            print("Modification successful.")
        else:
            print("Target bytes not found, no modification needed.")

if __name__ == "__main__":
    file_path = "options.txt"

    if len(sys.argv) == 2:
        file_path = sys.argv[1]

    modify_file(file_path)
