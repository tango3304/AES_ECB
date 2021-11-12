#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HeaderFile/FunctionDeclaration.h"//関数宣言
#include "HeaderFile/VariableDeclaration.h"//変数宣言
#include "SourceFile/SubBytes.c"//SubBytesの処理が記載
#include "SourceFile/MixColumns.c"//MixColumnsの処理が記載
#include "SourceFile/AddRoundKey.c"//AddRoundKeyの処理が記載
#define FILE_READ_SIZE (17)

//================
//AES暗号処理
//================
int main(){
    //ポインタ関数の変数宣言
    //【暗号化】
    P_Encryption_SBOX_CHANGE = Encryption_SBOX_CHANGE; //S-BOX表の値に変換処理の関数
    P_MixColumns_MDS_xor_0x02or01 = MixColumns_MDS_xor_0x02or01; //0x02と0x01計算処理の関数
    P_MixColumns_MDS_xor_0x03 = MixColumns_MDS_xor_0x03; //0x03計算処理の関数
    //【復号化】
    P_Decryption_SBOX_CHANGE = Decryption_SBOX_CHANGE; //S-BOX表の値に変換処理の関数
    P_InvMixColumns_x3 = InvMixColumns_x3;
    P_InvMixColumns_x2 = InvMixColumns_x2;
    P_InvMixColumns_x = InvMixColumns_x;
    P_InvMixColumns_1 = InvMixColumns_1;
    P_InvMixColumns_E = InvMixColumns_E;
    P_InvMixColumns_B = InvMixColumns_B;
    P_InvMixColumns_D = InvMixColumns_D;
    P_InvMixColumns_9 = InvMixColumns_9;


    //####################################
    //暗号対象のファイルの読み取り処理
    //####################################
    DecFread = fopen(Dec_FilePATH, "r"); //対象ファイルの中身を読み込む

    //16バイトずつファイルを読み取る
    while(fgets(Decryption_Fread_Value_tmp, FILE_READ_SIZE, DecFread) != NULL){

        //########################
        //Round_Keyの生成処理
        //########################
        if(Key_FReadExecution_COUNT == 0){
            Key_FReadExecution_COUNT++; //Round_Keyの生成処理 を1回だけ実行させるように制御
            Key_Fread = fopen(Key_FilePATH, "r"); //対象Keyファイルの中身を読み込む

            //1バイトずつファイルを読み取る
            while((Key_Fread_tmp[Key_FRead_COUNT] = fgetc(Key_Fread)) != EOF){
                Key_FRead_COUNT++; //ファイルを読み込んだ回数をカウント
            }

            //KeyFile.txtが16バイトの値でない場合の処理
            if(Key_FRead_COUNT != 16){
                printf("%s\n", "########################################");
                printf("%s\n", "# 規定値の16byteではありません         #");
                printf("%s\n", "#                                      #");
                printf("%s\n", "# KeyFile.txtを確認してください        #");
                printf("%s\n", "########################################");
                exit (0); //強制終了
            }

            fclose(Key_Fread); //Keyファイルの読み込み終了

            //==========================================================
            //Keyファイルの値をKeySchedule_Value多次元配列に格納
            //==========================================================
            for(RotWord_Vertical_COUNT = 0; RotWord_Vertical_COUNT < 4; RotWord_Vertical_COUNT++){
                for(RotWord_Beside_COUNT = 0; RotWord_Beside_COUNT < 4; RotWord_Beside_COUNT++){
                    KeySchedule_Value[RotWord_Vertical_COUNT][RotWord_Beside_COUNT] = (int)Key_Fread_tmp[RotWord_SubBytes_COUNT];
                    
                    RotWord_SubBytes_COUNT++; //Key_Fread_tmp配列のカウンタを+1ずつ足していく
                }
            }

            //==============================
            //10回分のAddRoundKeyを作成
            //==============================
            //Key_Fread_tmp配列の【3,7,11,15】の値を【7,11,15,3】の順に入れ替える（ShiftRowsの処理）
            for(KeySchedule_ShiftRows_Beside = 4; KeySchedule_ShiftRows_Beside < 45; KeySchedule_ShiftRows_Beside += 4){
                KeySchedule_Value_tmp = KeySchedule_Value[0][KeySchedule_ShiftRows_Beside - 1];
                KeySchedule_Value[0][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[1][KeySchedule_ShiftRows_Beside - 1];
                KeySchedule_Value[1][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[2][KeySchedule_ShiftRows_Beside - 1];
                KeySchedule_Value[2][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[3][KeySchedule_ShiftRows_Beside - 1];
                KeySchedule_Value[3][KeySchedule_ShiftRows_Beside] = KeySchedule_Value_tmp;

                //KeySchedule_Value配列の一部の値をS-BOX表で変換（SubBytes処理）
                for(KeySchedule_SubBytes_Vertical = 0; KeySchedule_SubBytes_Vertical < 4; KeySchedule_SubBytes_Vertical++){
                    KeySchedule_Value[KeySchedule_SubBytes_Vertical][KeySchedule_ShiftRows_Beside] = P_Encryption_SBOX_CHANGE(KeySchedule_Value[KeySchedule_SubBytes_Vertical][KeySchedule_ShiftRows_Beside]);
                }

                //KeySchedule_Valueの値とSubBytesした値とRconの値をXORで計算
                KeySchedule_Value[0][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[0][KeySchedule_ShiftRows_Beside - 4] ^ KeySchedule_Value[0][KeySchedule_ShiftRows_Beside] ^ Rcon[0][Rcon_COUNT];
                KeySchedule_Value[1][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[1][KeySchedule_ShiftRows_Beside - 4] ^ KeySchedule_Value[1][KeySchedule_ShiftRows_Beside] ^ Rcon[1][Rcon_COUNT];
                KeySchedule_Value[2][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[2][KeySchedule_ShiftRows_Beside - 4] ^ KeySchedule_Value[2][KeySchedule_ShiftRows_Beside] ^ Rcon[2][Rcon_COUNT];
                KeySchedule_Value[3][KeySchedule_ShiftRows_Beside] = KeySchedule_Value[3][KeySchedule_ShiftRows_Beside - 4] ^ KeySchedule_Value[3][KeySchedule_ShiftRows_Beside] ^ Rcon[3][Rcon_COUNT];
                
                Rcon_COUNT++; //AddRoundKey.cのRcon配列のカウンタを+1ずつ足していく

                //KeySchedule_Valueの値と【KeySchedule_XOR_Beside - 1】の値をXORで計算
                KeySchedule_XOR_Beside = KeySchedule_ShiftRows_Beside;
                for(KeySchedule_XOR_COUNT = 3; KeySchedule_XOR_COUNT > 0; KeySchedule_XOR_COUNT--){
                    KeySchedule_XOR_Beside++; //KeySchedule_ShiftRows_Beside + 1 の配列に格納

                    KeySchedule_Value[0][KeySchedule_XOR_Beside] = KeySchedule_Value[0][KeySchedule_XOR_Beside - 4] ^ KeySchedule_Value[0][KeySchedule_XOR_Beside - 1];
                    KeySchedule_Value[1][KeySchedule_XOR_Beside] = KeySchedule_Value[1][KeySchedule_XOR_Beside - 4] ^ KeySchedule_Value[1][KeySchedule_XOR_Beside - 1];
                    KeySchedule_Value[2][KeySchedule_XOR_Beside] = KeySchedule_Value[2][KeySchedule_XOR_Beside - 4] ^ KeySchedule_Value[2][KeySchedule_XOR_Beside - 1];
                    KeySchedule_Value[3][KeySchedule_XOR_Beside] = KeySchedule_Value[3][KeySchedule_XOR_Beside - 4] ^ KeySchedule_Value[3][KeySchedule_XOR_Beside - 1];
                }
            }//【 10回分のAddRoundKeyを作成 】の終わり
        }//【 Round_Keyの生成処理 】の終わり


        //##############################
        //Initial_Rounds処理
        //##############################
        //=======================
        //InvAddRoundKeyの処理
        //=======================
        for(InvRounds_Value_COUNT = 0; InvRounds_Value_COUNT < 4; InvRounds_Value_COUNT++){
            for(InvRounds_Beside_COUNT = 0; InvRounds_Beside_COUNT < 4; InvRounds_Beside_COUNT++){
            State[InvRounds_Value_COUNT][InvRounds_Beside_COUNT] = Decryption_Fread_Value_tmp[InvAddRoundKey_COUNT] ^ KeySchedule_Value[InvRounds_Value_COUNT][36 + InvRounds_Beside_COUNT];
            InvAddRoundKey_COUNT++;
            }
        }
            InvAddRoundKey_COUNT = 0;

        //=======================
        //InvShiftRowsの処理
        //=======================
        //SubBytes配列の値シフトしてShiftRows配列に格納
        //＜２段落目＞
        InvShiftRows_Value_tmp = State[1][3];
        State[1][3] = State[1][2];
        State[1][2] = State[1][1];
        State[1][1] = State[1][0];
        State[1][0] = InvShiftRows_Value_tmp;
        //＜３段落目＞
        InvShiftRows_Value_tmp = State[2][2];
        State[2][2] = State[2][0];
        State[2][0] = InvShiftRows_Value_tmp;
        InvShiftRows_Value_tmp = State[2][3];
        State[2][3] = State[2][1];
        State[2][1] = InvShiftRows_Value_tmp;
        //＜４段落目＞
        InvShiftRows_Value_tmp = State[3][0];
        State[3][0] = State[3][1];
        State[3][1] = State[3][2];
        State[3][2] = State[3][3];
        State[3][3] = InvShiftRows_Value_tmp;

        //=======================
        //InvSubBytesの処理
        //=======================
        //S-BOX表で変換した値をSubBytes配列(int型)に格納
        for(File_and_Key_Vertical_COUNT = 0; File_and_Key_Vertical_COUNT < 4; File_and_Key_Vertical_COUNT++){
            for(File_and_Key_Beside_COUNT = 0; File_and_Key_Beside_COUNT < 4; File_and_Key_Beside_COUNT++){
                State[File_and_Key_Vertical_COUNT][File_and_Key_Beside_COUNT] = P_Decryption_SBOX_CHANGE(State[File_and_Key_Vertical_COUNT][File_and_Key_Beside_COUNT]);
            }
        }

        
        //##############################
        //Main_Rounds処理を9回実行
        //##############################
        for(RoundsMain_COUNT = 1; RoundsMain_COUNT < 10; RoundsMain_COUNT++){
            //=======================
            //InvAddRoundKeyの処理
            //=======================
            for(InvAddRoundKey_Beside_COUNT = 0; InvAddRoundKey_Beside_COUNT < 4; InvAddRoundKey_Beside_COUNT++){
                InvMixColumns[0][InvAddRoundKey_Beside_COUNT] = State[0][InvAddRoundKey_Beside_COUNT] ^ KeySchedule_Value[0][Decryption_KeySchedule_Value_COUNT - Decryption_KeySchedule_SubtractionCOUNT];
                InvMixColumns[1][InvAddRoundKey_Beside_COUNT] = State[1][InvAddRoundKey_Beside_COUNT] ^ KeySchedule_Value[1][Decryption_KeySchedule_Value_COUNT - Decryption_KeySchedule_SubtractionCOUNT];
                InvMixColumns[2][InvAddRoundKey_Beside_COUNT] = State[2][InvAddRoundKey_Beside_COUNT] ^ KeySchedule_Value[2][Decryption_KeySchedule_Value_COUNT - Decryption_KeySchedule_SubtractionCOUNT];
                InvMixColumns[3][InvAddRoundKey_Beside_COUNT] = State[3][InvAddRoundKey_Beside_COUNT] ^ KeySchedule_Value[3][Decryption_KeySchedule_Value_COUNT - Decryption_KeySchedule_SubtractionCOUNT];

                Decryption_KeySchedule_SubtractionCOUNT--;
            }
            Decryption_KeySchedule_SubtractionCOUNT = 3;
            Decryption_KeySchedule_Value_COUNT -= 4; //KeySchedule_Valueのカウンタを-4ずつデクリメント

            //=======================
            //InvMixColumnsの処理
            //=======================
            //ガロア体の処理
            for(InvMixColumns_COUNT = 0; InvMixColumns_COUNT < 4; InvMixColumns_COUNT++){
                State[0][InvMixColumns_COUNT] = P_InvMixColumns_E(InvMixColumns[0][InvMixColumns_COUNT]) ^ P_InvMixColumns_B(InvMixColumns[1][InvMixColumns_COUNT]) ^ P_InvMixColumns_D(InvMixColumns[2][InvMixColumns_COUNT]) ^ P_InvMixColumns_9(InvMixColumns[3][InvMixColumns_COUNT]);
                State[1][InvMixColumns_COUNT] = P_InvMixColumns_9(InvMixColumns[0][InvMixColumns_COUNT]) ^ P_InvMixColumns_E(InvMixColumns[1][InvMixColumns_COUNT]) ^ P_InvMixColumns_B(InvMixColumns[2][InvMixColumns_COUNT]) ^ P_InvMixColumns_D(InvMixColumns[3][InvMixColumns_COUNT]);
                State[2][InvMixColumns_COUNT] = P_InvMixColumns_D(InvMixColumns[0][InvMixColumns_COUNT]) ^ P_InvMixColumns_9(InvMixColumns[1][InvMixColumns_COUNT]) ^ P_InvMixColumns_E(InvMixColumns[2][InvMixColumns_COUNT]) ^ P_InvMixColumns_B(InvMixColumns[3][InvMixColumns_COUNT]);
                State[3][InvMixColumns_COUNT] = P_InvMixColumns_B(InvMixColumns[0][InvMixColumns_COUNT]) ^ P_InvMixColumns_D(InvMixColumns[1][InvMixColumns_COUNT]) ^ P_InvMixColumns_9(InvMixColumns[2][InvMixColumns_COUNT]) ^ P_InvMixColumns_E(InvMixColumns[3][InvMixColumns_COUNT]);
            }

            //=======================
            //InvShiftRowsの処理
            //=======================
            //SubBytes配列の値シフトしてShiftRows配列に格納
            //＜２段落目＞
            InvShiftRows_Value_tmp = State[1][3];
            State[1][3] = State[1][2];
            State[1][2] = State[1][1];
            State[1][1] = State[1][0];
            State[1][0] = InvShiftRows_Value_tmp;
            //＜３段落目＞
            InvShiftRows_Value_tmp = State[2][2];
            State[2][2] = State[2][0];
            State[2][0] = InvShiftRows_Value_tmp;
            InvShiftRows_Value_tmp = State[2][3];
            State[2][3] = State[2][1];
            State[2][1] = InvShiftRows_Value_tmp;
            //＜４段落目＞
            InvShiftRows_Value_tmp = State[3][0];
            State[3][0] = State[3][1];
            State[3][1] = State[3][2];
            State[3][2] = State[3][3];
            State[3][3] = InvShiftRows_Value_tmp;
            
            //=======================
            //InvSubBytesの処理
            //=======================
            //S-BOX表で変換した値をSubBytes配列(int型)に格納
            for(File_and_Key_Vertical_COUNT = 0; File_and_Key_Vertical_COUNT < 4; File_and_Key_Vertical_COUNT++){
                for(File_and_Key_Beside_COUNT = 0; File_and_Key_Beside_COUNT < 4; File_and_Key_Beside_COUNT++){
                    State[File_and_Key_Vertical_COUNT][File_and_Key_Beside_COUNT] = P_Decryption_SBOX_CHANGE(State[File_and_Key_Vertical_COUNT][File_and_Key_Beside_COUNT]);
                }
            }
        } //【 Main_Rounds処理を9回実行 】の終わり


        //##############################
        //Final_Round処理
        //##############################
        //=======================
        //InvAddRoundKeyの処理
        //=======================
        //暗号対象のファイルと暗号化キーファイルのXOR処理
        for(InvRounds_Value_COUNT = 0; InvRounds_Value_COUNT < 4; InvRounds_Value_COUNT++){
            State[0][InvRounds_Value_COUNT] ^= KeySchedule_Value[0][InvRounds_Value_COUNT];
            State[1][InvRounds_Value_COUNT] ^= KeySchedule_Value[1][InvRounds_Value_COUNT];
            State[2][InvRounds_Value_COUNT] ^= KeySchedule_Value[2][InvRounds_Value_COUNT];
            State[3][InvRounds_Value_COUNT] ^= KeySchedule_Value[3][InvRounds_Value_COUNT];
        }
        Decryption_KeySchedule_Value_COUNT = 35; //KeySchedule_Valueのカウンタを35にリセット
        //【 Final_Round処理 】の終わり

        //=====================================
        //暗号化した値をファイルに書き込む
        //=====================================
        Decryption_Fwrite = fopen(Decryption_FilePATH, "a"); //ファイルが無ければ、新規ファイルの作成＆書き込み

        for(Fwrite_Vertical_COUNT = 0; Fwrite_Vertical_COUNT < 4; Fwrite_Vertical_COUNT++){
            for(Fwrite_Beside_COUNT = 0; Fwrite_Beside_COUNT < 4; Fwrite_Beside_COUNT++){
                Decryption_Value[Fwrite_Vertical_COUNT][Fwrite_Beside_COUNT] = (char)State[Fwrite_Vertical_COUNT][Fwrite_Beside_COUNT];
                fprintf(Decryption_Fwrite, "%c", Decryption_Value[Fwrite_Vertical_COUNT][Fwrite_Beside_COUNT]); //ファイルに書き込む
            }
        }
        fclose(Decryption_Fwrite); //ファイルの書き込み終了
        //【 Final_Round処理 】の終わり
    }//【 暗号対象のファイルの読み取り処理 】の終わり

    fclose(DecFread); //対象ファイルの読み込み終了
}
