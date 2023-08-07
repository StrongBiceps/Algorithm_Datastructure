#include <stdio.h>

int main() {
    FILE* sourceFile, * destinationFile;
    char sourceFileName[] = "astartes.jpg";
    char destinationFileName[] = "destination.jpg";

    // �ҽ� ���� ����
    fopen_s(&sourceFile, sourceFileName, "rb"); // "rb"�� ���̳ʸ� ���� �б⸦ �ǹ�
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // ��� ���� ����
    fopen_s(&destinationFile,destinationFileName, "wb"); // "wb"�� ���̳ʸ� ���� ���⸦ �ǹ�
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile); // �ҽ� ���� �ݱ�
        return 1;
    }

    // ���� ����
    const int bufferSize = 1024; // ������ �������� ���� ũ��
    char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    // ���� �ݱ�
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully\n");

    return 0;
}
