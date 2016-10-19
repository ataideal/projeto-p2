#ifndef COMP_DESCOMP_H_INCLUDED
#define COMP_DESCOMP_H_INCLUDED

int get_bit_at_position(unsigned int character, int position);
int set_bit_at_position(unsigned int character, int position);
char* get_extension(char *path);
unsigned int get_extension_length(char *ext);
unsigned int get_filename_length(char *path, unsigned int tam_ext);
unsigned int get_password_length(char *password);
unsigned char* get_filename(char *path, unsigned int tam_ext);
unsigned char* createMd5(const char* password);
void descomprimir(FILE *input_file,char * path);
unsigned int get_ext_length(FILE* input_file);
char * get_ext(FILE* input_file, int ext_length);
char * get_password(FILE* input_file);
unsigned int get_filename_length_file(FILE* input_file);
char * get_filename_file(FILE* input_file,int filename_length);
FILE* create_dir(FILE* json);
FILE* create_json(char *path,FILE *temp_json);
void descompressao_completa(FILE *input_file,char * md5);
void print_ext_length_in_file(FILE * output_file,unsigned int ext_length);
void print_ext_in_file(FILE * output_file,char * ext);
void print_md5_in_file(FILE * output_file,unsigned char *md5);
void print_name_length_in_file(FILE * output_file,unsigned int filename_length);
void print_name_in_file(FILE * output_file,unsigned char *filename);
void comprimir (FILE * arquivo,char * path,char * output);
void compressao_completa(FILE * arquivo,char * path,unsigned char * md5, char * ext,unsigned int ext_length,unsigned char * filename,unsigned int filename_length);
void compressao_tripla (FILE * arquivo,char * path,unsigned char * md5, char * ext,unsigned int ext_length,unsigned char * filename,unsigned int filename_length);
void descompressao_tripla(FILE * input_file, unsigned char * md5);


#endif // COMP_DESCOMP_H_INCLUDED
