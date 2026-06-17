#include <stdio.h>

#define TITLE_LEN  50

typedef struct {
    int number;
    char title[TITLE_LEN];
} Book;


int main(void)
{
    FILE *fp = fopen("books.bin", "rb");
    Book book;
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }
    
    while (1) {        
        size_t title_len = fread(book.title, 1, TITLE_LEN, fp);
        if (title_len == 0) break; // 파일 끝 또는 오류
        
        book.title[title_len] = '\0'; // 문자열 끝을 명확히 표시
        fread(&book.number, sizeof(int), 1, fp); // 개수 읽기
        
        printf("제목: %s, 개수: %d\n", book.title, book.number);
    }   
    return 0;
}