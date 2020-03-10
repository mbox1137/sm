struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    // здесь потребуется добавить поля для реализации буферизованного чтения
    int count;		 //осталось символов в буф
    int ind;		 //номер символа на выдачу
};
struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    // здесь потребуется добавить поля для реализации буферизованной записи
    int count;		 //осталось символов в буф
    int ind;		 //номер символа на выдачу
};
int nextchar();
int lastchar();
void myputchar(int ic);
__attribute__ ((fastcall)) void writechar(int ic, struct FileWriteState *st);
__attribute__ ((fastcall)) void flush(struct FileWriteState *st);
void myexit(int ret_val);
struct FileReadState *stin;
struct FileWriteState *stout;
