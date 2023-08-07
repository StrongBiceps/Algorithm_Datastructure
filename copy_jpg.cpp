#include <stdio.h>

int main() {
    FILE* sourceFile, * destinationFile;
    char sourceFileName[] = "astartes.jpg";
    char destinationFileName[] = "destination.jpg";

    // 소스 파일 열기
    fopen_s(&sourceFile, sourceFileName, "rb"); // "rb"는 바이너리 모드로 읽기를 의미
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // 대상 파일 열기
    fopen_s(&destinationFile,destinationFileName, "wb"); // "wb"는 바이너리 모드로 쓰기를 의미
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile); // 소스 파일 닫기
        return 1;
    }

    // 파일 복사
    const int bufferSize = 1024; // 복사할 데이터의 버퍼 크기
    char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    // 파일 닫기
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully\n");

    return 0;
}
