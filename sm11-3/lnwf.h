struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    // здесь потребуется добавить поля для реализации буферизованного чтения
};
struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    // здесь потребуется добавить поля для реализации буферизованной записи
};
int nextchar(struct FileReadState *st);
int lastchar(struct FileReadState *st);
void writechar(struct FileWriteState *st, int ic);
void flush(struct FileWriteState *st);
void myexit(int ret_val);
struct FileReadState *stin;
struct FileWriteState *stout;
