//***********************************************************************************************//
//* formation.cpp										*//
//***********************************************************************************************//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
#include "formation.h"											// formationヘッダファイル読み込み
//-----------------------------------------------------------------------------------------------//


//-- [メッセージ表示関数] -----------------------------------------------------------------------//
//- void message_display(unsigned int message_number)						-//
//- 機能   : メッセージの表示を行う								-//
//- 引数   : (unsigned int) メッセージ番号							-//
//- 戻り値 : (void)         なし								-//
//-----------------------------------------------------------------------------------------------//
void message_display(unsigned int message_number)
{

	//-- [メッセージ処理] -------------------------------------------------------------------//

	switch(message_number){										// メッセージ番号チェック

		case PROGRAM_BEGINNING:									// メッセージ0

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Program Beginning                        ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case PROGRAM_END:									// メッセージ1

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Program End                              ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case INITIALIZATION_BEGINNING:								// メッセージ2

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Initialization Beginning                 ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case INITIALIZATION_END:								// メッセージ3

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Initialization End                       ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case THE_MAIN_PROGRAM_BEGINNING:							// メッセージ4

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ The Main Program Beginning               ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case THE_MAIN_PROGRAM_END:								// メッセージ5

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ The Main Program End                     ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case FILE_OPEN_FAILURE:									// メッセージ6

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Initialization Completion                ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case ROS:										// メッセージ7

			printf("[ kyoto/formation           ]");					// メッセージ表示
			printf("[ Initialization Completion                ]");				// メッセージ表示
			printf("[ ROS                                      ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		default:										// デフォルト

			break;										// ブレイク

	}

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//



//-- [INIファイル読み込み関数] ------------------------------------------------------------------//
//- int ini_file_read(char* filename, struct Initialization *init_data)				-//
//- 機能   : INIファイルの読み込みを行う							-//
//- 引数   : (char *)                  ファイルディスクリプタポインタ				-//
//-          (struct Initialization *) 初期化データ格納構造体ポインタ				-//
//- 戻り値 : (int)                     初期化成功/失敗 [成功 = SUCCESS | 失敗 = FAILURE]	-//
//-----------------------------------------------------------------------------------------------//
int ini_file_read(char* filename, struct Initialization *init_data)
{

	//-- [変数宣言] -------------------------------------------------------------------------//

	char line[LINE_SIZE];										// 1行データ格納配列
	FILE *fd;											// ファイルディスクリプタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [ファイルオープン] -----------------------------------------------------------------//

	if((fd = fopen(filename, "r")) == NULL) return FAILURE;						// ファイルオープン

	//---------------------------------------------------------------------------------------//


	//-- [データ処理] -----------------------------------------------------------------------//

	while(fgets(line, LINE_SIZE, fd) != NULL){							// 1行読み込み

		line[strlen(line) - 1] = 0x00;								// 改行文字処理

		if(strstr(line, JOY_UP_THRESHOLD) != NULL)						// キーチェック
			init_data->up_threshold = atof(&line[strlen(JOY_UP_THRESHOLD)]);			// データ格納
		else if(strstr(line, JOY_DOWN_THRESHOLD) != NULL)					// キーチェック
			init_data->down_threshold = atof(&line[strlen(JOY_DOWN_THRESHOLD)]);		// データ格納
		else if(strstr(line, JOY_LEFT_THRESHOLD) != NULL)					// キーチェック
			init_data->left_threshold = atof(&line[strlen(JOY_LEFT_THRESHOLD)]);		// データ格納
		else if(strstr(line, JOY_RIGHT_THRESHOLD) != NULL)					// キーチェック
			init_data->right_threshold = atof(&line[strlen(JOY_RIGHT_THRESHOLD)]);		// データ格納
		else if(strstr(line, TWIST_FORWARD_MAXIMUM_VELOCITY) != NULL)				// キーチェック
			init_data->forward_maximum_velocity
				= atof(&line[strlen(TWIST_FORWARD_MAXIMUM_VELOCITY)]);			// データ格納
		else if(strstr(line, TWIST_BACKWARD_MAXIMUM_VELOCITY) != NULL)				// キーチェック
			init_data->backward_maximum_velocity
				= atof(&line[strlen(TWIST_BACKWARD_MAXIMUM_VELOCITY)]);			// データ格納
		else if(strstr(line, TWIST_CCW_MAXIMUM_ANGULAR_VELOCITY) != NULL)			// キーチェック
			init_data->ccw_maximum_angular_velocity
				= atof(&line[strlen(TWIST_CCW_MAXIMUM_ANGULAR_VELOCITY)]);		// データ格納
		else if(strstr(line, TWIST_CW_MAXIMUM_ANGULAR_VELOCITY) != NULL)			// キーチェック
			init_data->cw_maximum_angular_velocity
				= atof(&line[strlen(TWIST_CW_MAXIMUM_ANGULAR_VELOCITY)]);		// データ格納

	}

	//---------------------------------------------------------------------------------------//


	//-- [ファイルクローズ] -----------------------------------------------------------------//

	fclose(fd);											// ファイルクローズ

	//---------------------------------------------------------------------------------------//


	return SUCCESS;											// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//
