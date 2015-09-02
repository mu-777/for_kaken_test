//***********************************************************************************************//
//* main.cpp									     2015/06/10 *//
//*												*//
//* encoder_kohga3_1										*//
//*												*//
//*								(c) HAREHIME 2015 NITYC H.MAEDA *//
//***********************************************************************************************//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
#include "encoder_kohga3_1.h"										// encoder_kohga3_1
													//  ヘッダファイル読み込み
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

	using ros::init;										// ros::init指定
	using ros::ok;											// ros::ok指定
	using ros::NodeHandle;										// ros::NodeHandle指定
	using ros::Publisher;										// ros::Publisher指定
	using ros::Rate;										// ros::Rate指定
	using ros::Time;										// ros::Time指定
	using geometry_msgs::TwistStamped;								// geometry_msgs::TwistStamped指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// ROS処理
	TwistStamped twist_in_kohga3_1;									// 速度指令格納構造体

	// メッセージ表示
	message_display(PROGRAM_BEGINNING);								// メッセージ表示関数
	message_display(INITIALIZATION_BEGINNING);							// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	//-- [ROS初期化] ------------------------------------------------------------------------//

	// ROS処理初期化
	init(argc, argv, "encoder_kohga3_1");								// ROS初期化
	NodeHandle twist_in_kohga3_1_node;								// ノードハンドル生成
	Publisher twist_in_kohga3_1_msg
		= twist_in_kohga3_1_node.advertise<TwistStamped>("twist_in_kohga3_1", 1000);		// パブリッシャ生成
	Rate loop_rate(100);										// ループ頻度設定

	// ROS出力初期化
	twist_in_kohga3_1.header.seq      = 0;								// シーケンスナンバー初期化
	twist_in_kohga3_1.header.stamp    = Time::now();						// タイムスタンプ初期化
	twist_in_kohga3_1.header.frame_id = "";								// フレームID初期化
	twist_in_kohga3_1.twist.linear.x  = 1.0;							// 速度ベクトルx成分初期化
	twist_in_kohga3_1.twist.linear.y  = 0.0;							// 速度ベクトルy成分初期化
	twist_in_kohga3_1.twist.linear.z  = 0.0;							// 速度ベクトルz成分初期化
	twist_in_kohga3_1.twist.angular.x = 0.0;							// 角速度ベクトルx成分初期化
	twist_in_kohga3_1.twist.angular.y = 0.0;							// 角速度ベクトルy成分初期化
	twist_in_kohga3_1.twist.angular.z = 1.0;							// 角速度ベクトルz成分初期化

	// メッセージ表示
	message_display(ROS);										// メッセージ表示関数
	message_display(INITIALIZATION_END);								// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	//-- [メインプログラム] -----------------------------------------------------------------//

	// メッセージ表示
	message_display(THE_MAIN_PROGRAM_BEGINNING);							// メッセージ表示関数

	// メインループ
	while(ok()){											// メインループ


		//-- [メッセージ出力処理] -------------------------------------------------------//

		twist_in_kohga3_1.header.stamp     = Time::now();					// タイムスタンプ格納
		twist_in_kohga3_1.twist.linear.x  += 0.001;						// 速度ベクトルx成分格納
		twist_in_kohga3_1.twist.angular.z += 0.001;						// 角速度ベクトルz成分格納
		if(twist_in_kohga3_1.twist.linear.x > 2.0)
			twist_in_kohga3_1.twist.linear.x = 1.0;						// 速度ベクトルx成分格納
		if(twist_in_kohga3_1.twist.angular.z > 2.0)
			twist_in_kohga3_1.twist.angular.z = 1.0;					// 角速度ベクトルz成分格納
		twist_in_kohga3_1_msg.publish(twist_in_kohga3_1);					// ROSメッセージ発信
		loop_rate.sleep();									// 待機

		//-------------------------------------------------------------------------------//


	}

	//---------------------------------------------------------------------------------------//


	//-- [プログラム終了処理] ---------------------------------------------------------------//

	// メッセージ表示
	printf("\n");											// メッセージ表示
	message_display(THE_MAIN_PROGRAM_END);								// メッセージ表示関数
	message_display(PROGRAM_END);									// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	return SUCCESS;											// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//
