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
		
	AuHd ah = {0x2e736e64,24,0xffffffff,"エンコードの種類","サンプリングレート","チャンネル数"};
	//データ長は不明(0xffffffff)でOK
 
	if ((AUFile = fopen("sample.au", "wb")) == NULL) {
		printf("ファイルを書き込みできません");
		exit(1);
	}//作成するSUNオーディオファイル

	if((TextFile=fopen("sample.txt","rb"))==NULL){
		return(-1);			
	}//PCMデータのテキストファイル読み取り
		
		
	for(int i=0;i<44100;i++) //サンプリングレート数に対する書き出すサンプルの量を入力
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
