//***********************************************************************************************//
//* decoder_kohga3_2.cpp									*//
//***********************************************************************************************//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
#include "decoder_kohga3_2.h"										// decoder_kohga3_2
													//  ヘッダファイル読み込み
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

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ Program Beginning                        ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case PROGRAM_END:									// メッセージ1

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ Program End                              ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case INITIALIZATION_BEGINNING:								// メッセージ2

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ Initialization Beginning                 ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case INITIALIZATION_END:								// メッセージ3

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ Initialization End                       ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case THE_MAIN_PROGRAM_BEGINNING:							// メッセージ4

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ The Main Program Beginning               ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case THE_MAIN_PROGRAM_END:								// メッセージ5

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
			printf("[ The Main Program End                     ]");				// メッセージ表示
			printf("[ ---------------------------------------- ]\n");			// メッセージ表示
			fflush(stdout);									// バッファフラッシュ [printf表示用]
			break;										// ブレイク

		case ROS:										// メッセージ6

			printf("[ kyoto/decoder_kohga3_2    ]");					// メッセージ表示
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
