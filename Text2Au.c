//テキストファイルをAUファイルに変換するプログラム
//PCMデータがテキスト形式で書かれたものをAUファイルに変換して再生できる様にする
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
typedef struct au_filehdr {
	uint32_t au_magic;       /* マジックナンバー(.snd) */
	uint32_t au_offset;      /* オーディオデータが記録されているバイトオフセット */
	uint32_t au_data_size;   /* データ長（バイト） */
	uint32_t au_encoding;    /* エンコードの種別 */
	uint32_t au_sample_rate; /* 一秒あたりのサンプル数 */
	uint32_t au_channels;    /* チャンネル数 */
} AuHd;
 
int main() {
	
	FILE *TextFile;
	FILE *AUFile;
		
	AuHd ah = {0x2e736e64,24,0xffffffff,3,11025,1};
	//データ長は不明(0xffffffffでOK)
 
	if ((AUFile = fopen("sample.au", "wb")) == NULL) {
				printf("ファイル '%s' が書き込みオープンできません", "sample.au");
					exit(1);
		}

	if((TextFile=fopen("sample.txt","rb"))==NULL){
						return(-1);			
		}
		
		
	for(int i=0;i<60000;i++) //テキストの数字の任意の数を指定
		{
			unsigned short a;
			double d;
			if(fscanf(TextFile, "%lf", &d )==EOF){
				break;
				}
			a = d;
			fwrite(&a,sizeof(signed short),1,AUFile);
		}
		
	fseek(AUFile, 0, SEEK_SET);
	fwrite(&ah, sizeof(ah), 1, AUFile);
	
	fclose(AUFile);
	fclose(TextFile);
	
    return 0;
 }
