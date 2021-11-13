#ifndef Variable_IncludeGuard
#define Variable_IncludeGuard
//変数宣言

//=======================
//commonkey.c
//=======================
/*main関数の全体の処理回数*/
int OverallProcessing = 0;

/*多重起動制御のハンドル設定*/
HANDLE hMSP;

/*ポインタ関数の変数宣言*/
//【暗号化】
int (* P_Encryption_SBOX_CHANGE)(int); //S-BOX表の値に変換処理の関数ポインタ
int (* P_MixColumns_MDS_xor_0x02or01)(int, int); //0x02と0x01計算処理の関数ポインタ
int (* P_MixColumns_MDS_xor_0x03)(int, int); //0x03計算処理の関数ポインタ
//【復号化】
int (* P_Decryption_SBOX_CHANGE)(int); //S-BOX表の値に変換処理の関数ポインタ
int (* P_InvMixColumns_x3)(int);
int (* P_InvMixColumns_x2)(int);
int (* P_InvMixColumns_x)(int);
int (* P_InvMixColumns_1)(int);
int (* P_InvMixColumns_E)(int);
int (* P_InvMixColumns_B)(int);
int (* P_InvMixColumns_D)(int);
int (* P_InvMixColumns_9)(int);


/*暗号対象のファイルの読み取り処理*/
//【暗号化】
FILE *Fread;    //対象ファイル読み込み
char FilePATH[] = "TestFile/TargetFile.txt";//対象テキスト
unsigned char Fread_Value_tmp[16];
//【復号化】
FILE *DecFread;
char Dec_FilePATH[] = "TestFile/Encryption_FilePATH.txt";//対象テキスト
unsigned char Decryption_Fread_Value_tmp[16];

/*Round_Keyの生成処理*/
FILE *Key_Fread;//Keyファイル読み込み
char Key_FilePATH[] = "TestFile/KeyFile.txt";//対象Keyファイル
int Key_FRead_COUNT = 0;
int Key_FReadExecution_COUNT = 0;
char Key_Fread_tmp[16];

/*Keyファイルの値をKeySchedule_Value多次元配列に格納*/
int RotWord_Vertical_COUNT;
int RotWord_Beside_COUNT;
int KeySchedule_Value[4][52];
int RotWord_SubBytes_COUNT = 0;

/*Key_Fread_tmp配列の【3,7,11,15】の値を【7,11,15,3】の順に入れ替える（ShiftRowsの処理）*/
int KeySchedule_Value_tmp;
int KeySchedule_ShiftRows_Beside;

/*KeySchedule_Value配列の一部の値をS-BOX表で変換（SubBytes処理）*/
int KeySchedule_SubBytes_Vertical;

/*KeySchedule_Valueの値とSubBytesした値とRconの値をXORで計算*/
int Rcon_COUNT = 0;

/*KeySchedule_Valueの値と【KeySchedule_XOR_Beside - 1】の値をXORで計算*/
int KeySchedule_XOR_Beside;
int KeySchedule_XOR_COUNT;

/*暗号対象のファイルと暗号化キーファイルのXOR処理*/
int File_and_Key_COUNT;
unsigned char File_and_Key_Value_tmp[16];

/*Main_Rounds処理を9回実行*/
int RoundsMain_COUNT;

/*S-BOX表で変換した値をSubBytes配列(int型)に格納*/
int State[4][4];

/*暗号対象のファイルと暗号化キーファイルのXOR処理 で計算したRound_Keyの値をState多次元配列に格納*/
int File_and_Key_SubBytes_COUNT = 0;
int File_and_Key_Vertical_COUNT;
int File_and_Key_Beside_COUNT;

/*ShiftRowsの処理*/
//【暗号化】
int ShiftRows_Value_tmp;
/*InvShiftRowsの処理*/
//【復号化】
int InvShiftRows_Value_tmp;

/*MixColumnsの処理*/
//【暗号化】
int MixColumns[4][4];
int MixColumns_COUNT;
/*InvMixColumnsの処理*/
//【復号化】
int InvMixColumns[4][4];
int InvMixColumns_COUNT;

/*AddRoundKeyの処理*/
//【暗号化】
int AddRoundKey_Beside_COUNT;
int KeySchedule_Value_COUNT = 0;
/*InvAddRoundKeyの処理*/
//【復号化】
int InvRounds_Value_COUNT;
int InvRounds_Beside_COUNT;
int InvAddRoundKey_COUNT = 0;
/*InvAddRoundKeyの処理（Main_Rounds処理を9回実行）*/
int InvAddRoundKey_Beside_COUNT;
int Decryption_KeySchedule_Value_COUNT = 35;
int Decryption_KeySchedule_SubtractionCOUNT = 3;

/*暗号化した値をファイルに書き込む*/
//【暗号化】
FILE *Fwrite; //暗号化を書き込む
char Encryption_FilePATH[] = "TestFile/Encryption_FilePATH.txt"; //暗号化テキスト
unsigned char Encryption_Value[4][4];
//【復号化】
FILE *Decryption_Fwrite; //復号化を書き込む
char Decryption_FilePATH[] = "TestFile/Decryption_FilePATH.txt"; //復号化テキスト
unsigned char Decryption_Value[4][4];
//【暗号化＆復号化】
int Fwrite_Vertical_COUNT;
int Fwrite_Beside_COUNT;


//=======================
//SubBytes.c
//=======================
/*S-BOX表の値に変換処理*/
int TenDigits; //10桁関連の変数
int aDigit;    //1桁関連の変数


//=======================
//MixColumns.c
//=======================
/*0x02と0x01の計算処理関数*/
//【暗号化】
int MixColumns_Value;   //MixColumn_TenDigitsとMixColumn_aDigitを連結させた値
int MixColumn_aDigit;   //1桁目の値
int MixColumn_MoveUP;   //1桁目の繰り上がりの値
int MixColumn_TenDigits;//2桁目の値

/*[x3乗,x2乗,x,1]の計算処理関数*/
//【復号化】
int InvMix_COUNT;
int InvMixColumn_aDigit;   //1桁目の値
int InvMixColumn_MoveUP;   //1桁目の繰り上がりの値
int InvMixColumn_TenDigits;//2桁目の値

/*[E,B,D,9]の計算処理関数*/
//【復号化】
int x3_Value;
int x2_Value;
int x_Value;
int _1Value;

int InvMixColumns_E_Value;
int InvMixColumns_B_Value;
int InvMixColumns_D_Value;
int InvMixColumns_9_Value;
#endif //Variable_IncludeGuard
