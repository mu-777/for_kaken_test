//***********************************************************************************************//
//* main.cpp									     2015/08/21 *//
//*												*//
//* decoder_kohga3_2										*//
//*												*//
//*								(c) HAREHIME 2015 NITYC H.MAEDA *//
//***********************************************************************************************//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
#include "decoder_kohga3_2.h"										// decoder_kohga3_2
													//  ヘッダファイル読み込み
//-----------------------------------------------------------------------------------------------//


//-- [プロトタイプ宣言] -------------------------------------------------------------------------//
void twist_out_kohga3_2_callback(const geometry_msgs::TwistStamped::ConstPtr &);			// コールバック関数
//-----------------------------------------------------------------------------------------------//


//-- [メイン関数] -------------------------------------------------------------------------------//
//- int main(int argc, char *argv[])								-//
//- 機能   : メインのプログラム処理を行う							-//
//- 引数   : (int)   コマンドライン引数の数							-//
//-          (char*) コマンドライン引数								-//
//- 戻り値 : (int)   -										-//
//-----------------------------------------------------------------------------------------------//
int main(int argc, char *argv[])
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using geometry_msgs::TwistStamped;								// geometry_msgs::TwistStamped指定
	using ros::init;										// ros::init指定
	using ros::ok;											// ros::ok指定
	using ros::spinOnce;										// ros::spinOnce指定
	using ros::NodeHandle;										// ros::NodeHandle指定
	using ros::Rate;										// ros::Rate指定
	using ros::Subscriber;										// ros::Subscriber指定

	// メッセージ表示
	message_display(PROGRAM_BEGINNING);								// メッセージ表示関数
	message_display(INITIALIZATION_BEGINNING);							// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	//-- [ROS初期化] ------------------------------------------------------------------------//

	// ROS処理初期化
	init(argc, argv, "decoder_kohga3_2");								// ROS初期化
	NodeHandle twist_out_kohga3_2_node;								// ノードハンドル生成
	Subscriber twist_out_kohga3_2_msg = twist_out_kohga3_2_node.subscribe<TwistStamped>(
		"twist_out_kohga3_2", 1000, twist_out_kohga3_2_callback);				// サブスクライブ生成
	Rate loop_rate(100);										// ループ頻度設定

	// メッセージ表示
	message_display(ROS);										// メッセージ表示関数
	message_display(INITIALIZATION_END);								// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	//-- [メインプログラム] -----------------------------------------------------------------//

	// メッセージ表示
	message_display(THE_MAIN_PROGRAM_BEGINNING);							// メッセージ表示関数

	// メインループ
	while(ok()){											// メインループ


		//-- [コールバック処理] ---------------------------------------------------------//

		spinOnce();										// メッセージコールバック呼び出し
		loop_rate.sleep();									// 待機

		//-------------------------------------------------------------------------------//


	}

	//---------------------------------------------------------------------------------------//


	//-- [プログラム終了処理] ---------------------------------------------------------------//

	// メッセージ表示
	printf("\n\n\n\n\n\n\n\n\n");									// メッセージ表示
	message_display(THE_MAIN_PROGRAM_END);								// メッセージ表示関数
	message_display(PROGRAM_END);									// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	return SUCCESS;											// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void twist_out_kohga3_2_callback(const geometry_msgs::TwistStamped::ConstPtr&		-//
//-  twist_out_kohga3_2)									-//
//- 機能   : コールバック処理を行う [rostime]							-//
//- 引数   : (const geometry_msgs::TwistStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                         なし				-//
//-----------------------------------------------------------------------------------------------//
void twist_out_kohga3_2_callback(const geometry_msgs::TwistStamped::ConstPtr& twist_out_kohga3_2)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 sequence number       ]");						// メッセージ表示
	printf("[ %010d                               ]\n", twist_out_kohga3_2->header.seq);		// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 timestamp             ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_out_kohga3_2->header.stamp.sec,
		twist_out_kohga3_2->header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 frame id              ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_out_kohga3_2->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 linear x              ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.linear.x);	// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 linear y              ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.linear.y);	// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 linear z              ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.linear.z);	// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 angular x             ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.angular.x);	// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 angular y             ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.angular.y);	// メッセージ表示
	printf("[ kyoto/decoder_kohga3_2    ]");							// メッセージ表示
	printf("[ twist_out_kohga3_2 angular z             ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_out_kohga3_2->twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 9);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//
