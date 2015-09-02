//***********************************************************************************************//
//* main.cpp									     2015/08/22 *//
//*												*//
//* kyoto/formation										*//
//*												*//
//*								(c) HAREHIME 2015 NITYC H.MAEDA *//
//***********************************************************************************************//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
#include "formation.h"											// formationヘッダファイル読み込み
//-----------------------------------------------------------------------------------------------//


//-- [DEBUG定義] --------------------------------------------------------------------------------//
#define DEBUG_JOY											// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_KOHGA3_1										// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_KOHGA3_2										// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_FRIGO_1										// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_FRIGO_2										// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_UMRS2009_1									// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_UMRS2009_2									// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_UMRS2010_1									// DEBUG定義 [デバッグ用]
#define DEBUG_POSITION_UMRS2010_2									// DEBUG定義 [デバッグ用]
#define DEBUG_SELECT_TWIST										// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_KOHGA3_1									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_KOHGA3_2									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_FRIGO_1									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_FRIGO_2									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_UMRS2009_1									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_UMRS2009_2									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_UMRS2010_1									// DEBUG定義 [デバッグ用]
#define DEBUG_TWIST_LEADER_UMRS2010_2									// DEBUG定義 [デバッグ用]
//-----------------------------------------------------------------------------------------------//


//-- [プロトタイプ宣言] -------------------------------------------------------------------------//
void joy_callback(const sensor_msgs::Joy::ConstPtr &);							// コールバック関数
void position_kohga3_1_callback(const kyoto::RelativePoseStamped::ConstPtr &);				// コールバック関数
void position_kohga3_2_callback(const kyoto::RelativePoseStamped::ConstPtr &);				// コールバック関数
void position_frigo_1_callback(const kyoto::RelativePoseStamped::ConstPtr &);				// コールバック関数
void position_frigo_2_callback(const kyoto::RelativePoseStamped::ConstPtr &);				// コールバック関数
void position_umrs2009_1_callback(const kyoto::RelativePoseStamped::ConstPtr &);			// コールバック関数
void position_umrs2009_2_callback(const kyoto::RelativePoseStamped::ConstPtr &);			// コールバック関数
void position_umrs2010_1_callback(const kyoto::RelativePoseStamped::ConstPtr &);			// コールバック関数
void position_umrs2010_2_callback(const kyoto::RelativePoseStamped::ConstPtr &);			// コールバック関数
//-----------------------------------------------------------------------------------------------//


//-- [変数宣言] ---------------------------------------------------------------------------------//
int button_flag;											// フラグ格納変数
int select_twist_flag;											// フラグ格納変数
int twist_leader_kohga3_1_flag;										// フラグ格納変数
int twist_leader_kohga3_2_flag;										// フラグ格納変数
int twist_leader_frigo_1_flag;										// フラグ格納変数
int twist_leader_frigo_2_flag;										// フラグ格納変数
int twist_leader_umrs2009_1_flag;									// フラグ格納変数
int twist_leader_umrs2009_2_flag;									// フラグ格納変数
int twist_leader_umrs2010_1_flag;									// フラグ格納変数
int twist_leader_umrs2010_2_flag;									// フラグ格納変数
struct Initialization init_data;									// 初期化データ格納構造体
kyoto::SelectStamped select_twist;									// 切替格納メッセージ
geometry_msgs::TwistStamped twist_leader_kohga3_1;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_kohga3_2;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_frigo_1;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_frigo_2;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_umrs2009_1;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_umrs2009_2;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_umrs2010_1;							// 速度ベクトル格納メッセージ
geometry_msgs::TwistStamped twist_leader_umrs2010_2;							// 速度ベクトル格納メッセージ
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
	using kyoto::RelativePoseStamped;								// kyoto::RelativePoseStamped指定
	using kyoto::SelectStamped;									// kyoto::SelectStamped指定
	using ros::init;										// ros::init指定
	using ros::ok;											// ros::ok指定
	using ros::spinOnce;										// ros::spinOnce指定
	using ros::NodeHandle;										// ros::NodeHandle指定
	using ros::Publisher;										// ros::Publisher指定
	using ros::Rate;										// ros::Rate指定
	using ros::Subscriber;										// ros::Subscriber指定
	using ros::Time;										// ros::Time指定
	using sensor_msgs::Joy;										// sensor_msgs::Joy指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	char filename[] = INI_FILE_NAME;								// ファイル名格納配列

	//---------------------------------------------------------------------------------------//


	//-- [変数初期化] -----------------------------------------------------------------------//

	// 変数初期化
	button_flag                             = OFF;							// フラグ初期化
	select_twist_flag                       = OFF;							// フラグ初期化
	twist_leader_kohga3_1_flag              = OFF;							// フラグ初期化
	twist_leader_kohga3_2_flag              = OFF;							// フラグ初期化
	twist_leader_frigo_1_flag               = OFF;							// フラグ初期化
	twist_leader_frigo_2_flag               = OFF;							// フラグ初期化
	twist_leader_umrs2009_1_flag            = OFF;							// フラグ初期化
	twist_leader_umrs2009_2_flag            = OFF;							// フラグ初期化
	twist_leader_umrs2010_1_flag            = OFF;							// フラグ初期化
	twist_leader_umrs2010_2_flag            = OFF;							// フラグ初期化

	// メッセージ表示
	message_display(PROGRAM_BEGINNING);								// メッセージ表示関数
	message_display(INITIALIZATION_BEGINNING);							// メッセージ表示関数

	// 初期値取得
	if(ini_file_read(filename, &init_data) == FAILURE){						// INIファイル読み込み関数

		message_display(FILE_OPEN_FAILURE);							// メッセージ表示
		exit(1);										// 異常終了

	}

	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Joy                ]");						// メッセージ表示
	printf("[ Up Threshold                 = %9.6f ]\n", init_data.up_threshold);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Joy                ]");						// メッセージ表示
	printf("[ Down Threshold               = %9.6f ]\n", init_data.down_threshold);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Joy                ]");						// メッセージ表示
	printf("[ Left Threshold               = %9.6f ]\n", init_data.left_threshold);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Joy                ]");						// メッセージ表示
	printf("[ Right Threshold              = %9.6f ]\n", init_data.right_threshold);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Twist              ]");						// メッセージ表示
	printf("[ Forward Maximum Velocity     = %9.6f ]\n", init_data.forward_maximum_velocity);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Twist              ]");						// メッセージ表示
	printf("[ Backward Maximum Velocity    = %9.6f ]\n", init_data.backward_maximum_velocity);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Twist              ]");						// メッセージ表示
	printf("[ CCW Maximum Angular Velocity = %9.6f ]\n", init_data.ccw_maximum_angular_velocity);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ Initialization Data : Twist              ]");						// メッセージ表示
	printf("[ CW Maximum Angular Velocity  = %9.6f ]\n", init_data.cw_maximum_angular_velocity);	// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示用]

	//---------------------------------------------------------------------------------------//


	//-- [ROS初期化] ------------------------------------------------------------------------//

	// ROS処理初期化
	init(argc, argv, "formation");									// ROS初期化
	NodeHandle joy_node;										// ノードハンドル生成
	NodeHandle position_kohga3_1_node;								// ノードハンドル生成
	NodeHandle position_kohga3_2_node;								// ノードハンドル生成
	NodeHandle position_frigo_1_node;								// ノードハンドル生成
	NodeHandle position_frigo_2_node;								// ノードハンドル生成
	NodeHandle position_umrs2009_1_node;								// ノードハンドル生成
	NodeHandle position_umrs2009_2_node;								// ノードハンドル生成
	NodeHandle position_umrs2010_1_node;								// ノードハンドル生成
	NodeHandle position_umrs2010_2_node;								// ノードハンドル生成
	NodeHandle select_twist_node;									// ノードハンドル生成
	NodeHandle twist_leader_kohga3_1_node;								// ノードハンドル生成
	NodeHandle twist_leader_kohga3_2_node;								// ノードハンドル生成
	NodeHandle twist_leader_frigo_1_node;								// ノードハンドル生成
	NodeHandle twist_leader_frigo_2_node;								// ノードハンドル生成
	NodeHandle twist_leader_umrs2009_1_node;							// ノードハンドル生成
	NodeHandle twist_leader_umrs2009_2_node;							// ノードハンドル生成
	NodeHandle twist_leader_umrs2010_1_node;							// ノードハンドル生成
	NodeHandle twist_leader_umrs2010_2_node;							// ノードハンドル生成
	Subscriber joy_msg = joy_node.subscribe<Joy>("joy", 1000, joy_callback);			// サブスクライブ生成
	Subscriber position_kohga3_1_msg = position_kohga3_1_node.subscribe<RelativePoseStamped>(
		"position_kohga3_1", 1000, position_kohga3_1_callback);					// サブスクライブ生成
	Subscriber position_kohga3_2_msg = position_kohga3_2_node.subscribe<RelativePoseStamped>(
		"position_kohga3_2", 1000, position_kohga3_2_callback);					// サブスクライブ生成
	Subscriber position_frigo_1_msg = position_frigo_1_node.subscribe<RelativePoseStamped>(
		"position_frigo_1", 1000, position_frigo_1_callback);					// サブスクライブ生成
	Subscriber position_frigo_2_msg = position_frigo_2_node.subscribe<RelativePoseStamped>(
		"position_frigo_2", 1000, position_frigo_2_callback);					// サブスクライブ生成
	Subscriber position_umrs2009_1_msg = position_umrs2009_1_node.subscribe<RelativePoseStamped>(
		"position_umrs2009_1", 1000, position_umrs2009_1_callback);				// サブスクライブ生成
	Subscriber position_umrs2009_2_msg = position_umrs2009_2_node.subscribe<RelativePoseStamped>(
		"position_umrs2009_2", 1000, position_umrs2009_2_callback);				// サブスクライブ生成
	Subscriber position_umrs2010_1_msg = position_umrs2010_1_node.subscribe<RelativePoseStamped>(
		"position_umrs2010_1", 1000, position_umrs2010_1_callback);				// サブスクライブ生成
	Subscriber position_umrs2010_2_msg = position_umrs2010_2_node.subscribe<RelativePoseStamped>(
		"position_umrs2010_2", 1000, position_umrs2010_2_callback);				// サブスクライブ生成
	Publisher select_twist_msg
		= select_twist_node.advertise<SelectStamped>("select_twist", 1000);			// パブリッシャ生成
	Publisher twist_leader_kohga3_1_msg
		= twist_leader_kohga3_1_node.advertise<TwistStamped>("twist_leader_kohga3_1", 1000);	// パブリッシャ生成
	Publisher twist_leader_kohga3_2_msg
		= twist_leader_kohga3_2_node.advertise<TwistStamped>("twist_leader_kohga3_2", 1000);	// パブリッシャ生成
	Publisher twist_leader_frigo_1_msg
		= twist_leader_frigo_1_node.advertise<TwistStamped>("twist_leader_frigo_1", 1000);	// パブリッシャ生成
	Publisher twist_leader_frigo_2_msg
		= twist_leader_frigo_2_node.advertise<TwistStamped>("twist_leader_frigo_2", 1000);	// パブリッシャ生成
	Publisher twist_leader_umrs2009_1_msg
		= twist_leader_umrs2009_1_node.advertise<TwistStamped>("twist_leader_umrs2009_1",
		1000);											// パブリッシャ生成
	Publisher twist_leader_umrs2009_2_msg
		= twist_leader_umrs2009_2_node.advertise<TwistStamped>("twist_leader_umrs2009_2",
		1000);											// パブリッシャ生成
	Publisher twist_leader_umrs2010_1_msg
		= twist_leader_umrs2010_1_node.advertise<TwistStamped>("twist_leader_umrs2010_1",
		1000);											// パブリッシャ生成
	Publisher twist_leader_umrs2010_2_msg
		= twist_leader_umrs2010_2_node.advertise<TwistStamped>("twist_leader_umrs2010_2",
		1000);											// パブリッシャ生成
	Rate loop_rate(100);										// ループ頻度設定

	// ROS出力初期化
	select_twist.header.seq                 = 0;							// シーケンスナンバー初期化
	select_twist.header.stamp               = Time::now();						// タイムスタンプ初期化
	select_twist.header.frame_id            = "";							// フレームID初期化
	select_twist.select_data[0]             = 0;							// 切替データ初期化
	select_twist.select_data[1]             = 0;							// 切替データ初期化
	select_twist.select_data[2]             = 0;							// 切替データ初期化
	select_twist.select_data[3]             = 0;							// 切替データ初期化
	select_twist.select_data[4]             = 0;							// 切替データ初期化
	select_twist.select_data[5]             = 0;							// 切替データ初期化
	select_twist.select_data[6]             = 0;							// 切替データ初期化
	select_twist.select_data[7]             = 0;							// 切替データ初期化
	twist_leader_kohga3_1.header.seq        = 0;							// シーケンスナンバー初期化
	twist_leader_kohga3_1.header.stamp      = Time::now();						// タイムスタンプ初期化
	twist_leader_kohga3_1.header.frame_id   = "";							// フレームID初期化
	twist_leader_kohga3_1.twist.linear.x    = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_kohga3_1.twist.linear.y    = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_kohga3_1.twist.linear.z    = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_kohga3_1.twist.angular.x   = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_kohga3_1.twist.angular.y   = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_kohga3_1.twist.angular.z   = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_kohga3_2.header.seq        = 0;							// シーケンスナンバー初期化
	twist_leader_kohga3_2.header.stamp      = Time::now();						// タイムスタンプ初期化
	twist_leader_kohga3_2.header.frame_id   = "";							// フレームID初期化
	twist_leader_kohga3_2.twist.linear.x    = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_kohga3_2.twist.linear.y    = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_kohga3_2.twist.linear.z    = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_kohga3_2.twist.angular.x   = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_kohga3_2.twist.angular.y   = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_kohga3_2.twist.angular.z   = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_frigo_1.header.seq         = 0;							// シーケンスナンバー初期化
	twist_leader_frigo_1.header.stamp       = Time::now();						// タイムスタンプ初期化
	twist_leader_frigo_1.header.frame_id    = "";							// フレームID初期化
	twist_leader_frigo_1.twist.linear.x     = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_frigo_1.twist.linear.y     = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_frigo_1.twist.linear.z     = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_frigo_1.twist.angular.x    = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_frigo_1.twist.angular.y    = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_frigo_1.twist.angular.z    = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_frigo_2.header.seq         = 0;							// シーケンスナンバー初期化
	twist_leader_frigo_2.header.stamp       = Time::now();						// タイムスタンプ初期化
	twist_leader_frigo_2.header.frame_id    = "";							// フレームID初期化
	twist_leader_frigo_2.twist.linear.x     = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_frigo_2.twist.linear.y     = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_frigo_2.twist.linear.z     = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_frigo_2.twist.angular.x    = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_frigo_2.twist.angular.y    = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_frigo_2.twist.angular.z    = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_umrs2009_1.header.seq      = 0;							// シーケンスナンバー初期化
	twist_leader_umrs2009_1.header.stamp    = Time::now();						// タイムスタンプ初期化
	twist_leader_umrs2009_1.header.frame_id = "";							// フレームID初期化
	twist_leader_umrs2009_1.twist.linear.x  = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_umrs2009_1.twist.linear.y  = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_umrs2009_1.twist.linear.z  = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_umrs2009_1.twist.angular.x = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_umrs2009_1.twist.angular.y = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_umrs2009_1.twist.angular.z = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_umrs2009_2.header.seq      = 0;							// シーケンスナンバー初期化
	twist_leader_umrs2009_2.header.stamp    = Time::now();						// タイムスタンプ初期化
	twist_leader_umrs2009_2.header.frame_id = "";							// フレームID初期化
	twist_leader_umrs2009_2.twist.linear.x  = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_umrs2009_2.twist.linear.y  = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_umrs2009_2.twist.linear.z  = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_umrs2009_2.twist.angular.x = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_umrs2009_2.twist.angular.y = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_umrs2009_2.twist.angular.z = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_umrs2010_1.header.seq      = 0;							// シーケンスナンバー初期化
	twist_leader_umrs2010_1.header.stamp    = Time::now();						// タイムスタンプ初期化
	twist_leader_umrs2010_1.header.frame_id = "";							// フレームID初期化
	twist_leader_umrs2010_1.twist.linear.x  = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_umrs2010_1.twist.linear.y  = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_umrs2010_1.twist.linear.z  = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_umrs2010_1.twist.angular.x = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_umrs2010_1.twist.angular.y = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_umrs2010_1.twist.angular.z = 0.0;							// 角速度ベクトルz成分初期化
	twist_leader_umrs2010_2.header.seq      = 0;							// シーケンスナンバー初期化
	twist_leader_umrs2010_2.header.stamp    = Time::now();						// タイムスタンプ初期化
	twist_leader_umrs2010_2.header.frame_id = "";							// フレームID初期化
	twist_leader_umrs2010_2.twist.linear.x  = 0.0;							// 速度ベクトルx成分初期化
	twist_leader_umrs2010_2.twist.linear.y  = 0.0;							// 速度ベクトルy成分初期化
	twist_leader_umrs2010_2.twist.linear.z  = 0.0;							// 速度ベクトルz成分初期化
	twist_leader_umrs2010_2.twist.angular.x = 0.0;							// 角速度ベクトルx成分初期化
	twist_leader_umrs2010_2.twist.angular.y = 0.0;							// 角速度ベクトルy成分初期化
	twist_leader_umrs2010_2.twist.angular.z = 0.0;							// 角速度ベクトルz成分初期化

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

		if(select_twist_flag == ON){								// 更新チェック

			select_twist_msg.publish(select_twist);						// ROSメッセージ発信
			select_twist_flag = OFF;							// フラグリセット

		}

		if(twist_leader_kohga3_1_flag == ON){							// 更新チェック

			twist_leader_kohga3_1_msg.publish(twist_leader_kohga3_1);			// ROSメッセージ発信
			twist_leader_kohga3_1_flag = OFF;						// フラグリセット

		}

		if(twist_leader_kohga3_2_flag == ON){							// 更新チェック

			twist_leader_kohga3_2_msg.publish(twist_leader_kohga3_2);			// ROSメッセージ発信
			twist_leader_kohga3_2_flag = OFF;						// フラグリセット

		}

		if(twist_leader_frigo_1_flag == ON){							// 更新チェック

			twist_leader_frigo_1_msg.publish(twist_leader_frigo_1);				// ROSメッセージ発信
			twist_leader_frigo_1_flag = OFF;						// フラグリセット

		}

		if(twist_leader_frigo_2_flag == ON){							// 更新チェック

			twist_leader_frigo_2_msg.publish(twist_leader_frigo_2);				// ROSメッセージ発信
			twist_leader_frigo_2_flag = OFF;						// フラグリセット

		}

		if(twist_leader_umrs2009_1_flag == ON){							// 更新チェック

			twist_leader_umrs2009_1_msg.publish(twist_leader_umrs2009_1);			// ROSメッセージ発信
			twist_leader_umrs2009_1_flag = OFF;						// フラグリセット

		}

		if(twist_leader_umrs2009_2_flag == ON){							// 更新チェック

			twist_leader_umrs2009_2_msg.publish(twist_leader_umrs2009_2);			// ROSメッセージ発信
			twist_leader_umrs2009_2_flag = OFF;						// フラグリセット

		}

		if(twist_leader_umrs2010_1_flag == ON){							// 更新チェック

			twist_leader_umrs2010_1_msg.publish(twist_leader_umrs2010_1);			// ROSメッセージ発信
			twist_leader_umrs2010_1_flag = OFF;						// フラグリセット

		}

		if(twist_leader_umrs2010_2_flag == ON){							// 更新チェック

			twist_leader_umrs2010_2_msg.publish(twist_leader_umrs2010_2);			// ROSメッセージ発信
			twist_leader_umrs2010_2_flag = OFF;						// フラグリセット

		}

		//-------------------------------------------------------------------------------//


		//-- [コールバック処理] ---------------------------------------------------------//

		spinOnce();										// メッセージコールバック呼び出し
		loop_rate.sleep();									// 待機

		//-------------------------------------------------------------------------------//


	}

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_JOY										// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");						// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_KOHGA3_1									// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_KOHGA3_2									// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_FRIGO_1									// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_FRIGO_2									// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_UMRS2009_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_UMRS2009_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_UMRS2010_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_POSITION_UMRS2010_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n\n\n\n");								// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_SELECT_TWIST									// デバッグ実行設定開始
	printf("\n\n\n");										// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_KOHGA3_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_KOHGA3_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_FRIGO_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_FRIGO_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_UMRS2009_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_UMRS2009_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_UMRS2010_1								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	#ifndef DEBUG_TWIST_LEADER_UMRS2010_2								// デバッグ実行設定開始
	printf("\n\n\n\n\n\n\n\n");									// メッセージ表示
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [プログラム終了処理] ---------------------------------------------------------------//

	// メッセージ表示
	message_display(THE_MAIN_PROGRAM_END);								// メッセージ表示関数
	message_display(PROGRAM_END);									// メッセージ表示関数

	//---------------------------------------------------------------------------------------//


	return SUCCESS;											// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void joy_callback(const sensor_msgs::Joy::ConstPtr& joy)					-//
//- 機能   : コールバック処理を行う [sensor_msgs/Joy]						-//
//- 引数   : (const sensor_msgs::Joy::ConstPtr&) 更新メッセージアドレス				-//
//- 戻り値 : (void)                              なし						-//
//-----------------------------------------------------------------------------------------------//
void joy_callback(const sensor_msgs::Joy::ConstPtr& joy)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_JOY										// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy sequence number                      ]");						// メッセージ表示
	printf("[ %010d                               ]\n", joy->header.seq);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy timestamp                            ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", joy->header.stamp.sec, joy->header.stamp.nsec);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy frame id                             ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << joy->header.frame_id;									// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[0]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[0]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[1]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[1]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[2]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[2]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[3]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[3]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[4]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[4]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy axes[5]                              ]");						// メッセージ表示
	printf("[ %9.6f                                ]\n", joy->axes[5]);				// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[0]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[0]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[1]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[1]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[2]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[2]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[3]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[3]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[4]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[4]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[5]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[5]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[6]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[6]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[7]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[7]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[8]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[8]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[9]                           ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[9]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[10]                          ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[10]);			// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ joy buttons[11]                          ]");						// メッセージ表示
	printf("[ %d                                        ]\n", joy->buttons[11]);			// メッセージ表示
	printf("\033[%dA", 21);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [メッセージ更新処理:select_twist] --------------------------------------------------//

	// ヘッダ処理
	select_twist.header.stamp    = joy->header.stamp;						// タイムスタンプ格納
	select_twist.header.frame_id = joy->header.frame_id;						// タイムスタンプ格納

	// ボタン処理
	if((button_flag == OFF) && (joy->buttons[8] == ON)){						// ボタン9チェック

		for(i = 0; i < 8; i++){									// ボタン1～8チェック

			if(joy->buttons[i] == ON){							// ボタンチェック

				select_twist.select_data[i]++;						// 切替データ格納
				if(select_twist.select_data[i] == 16) select_twist.select_data[i] = 0;	// 切替データリセット
				select_twist_flag = ON;							// フラグチェック

			}

		}

		button_flag = ON;									// フラグチェック

	}else if((button_flag == ON) && (joy->buttons[8] == OFF)){					// ボタン9チェック

		button_flag = OFF;									// フラグリセット

	}

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_SELECT_TWIST									// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ select_twist timestamp                   ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", select_twist.header.stamp.sec,
		select_twist.header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ select_twist frame id                    ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << select_twist.header.frame_id;								// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ select_twist select data                 ]");						// メッセージ表示
	printf("[ %2d %2d %2d %2d %2d %2d %2d %2d                  ]\n",
		select_twist.select_data[0], select_twist.select_data[1], select_twist.select_data[2],
		select_twist.select_data[3], select_twist.select_data[4], select_twist.select_data[5],
		select_twist.select_data[6], select_twist.select_data[7]);				// メッセージ表示
	printf("\033[%dA", 3);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [メッセージ更新処理:twist_leader_*] ------------------------------------------------//

	// ヘッダ処理
	twist_leader_kohga3_1.header.stamp    = joy->header.stamp;					// タイムスタンプ格納
	twist_leader_kohga3_1.header.frame_id = joy->header.frame_id;					// フレームID格納

	// ジョイスティック左の上下処理
	if(joy->axes[1] > init_data.up_threshold){							// ジョイスティック左の上チェック

		twist_leader_kohga3_1.twist.linear.x
			= init_data.forward_maximum_velocity * (joy->axes[1] - init_data.up_threshold)
			/ (1.0 - init_data.up_threshold);						// 速度ベクトルx成分格納
		twist_leader_kohga3_1_flag   = ON;							// フラグチェック
		twist_leader_kohga3_2_flag   = ON;							// フラグチェック
		twist_leader_frigo_1_flag    = ON;							// フラグチェック
		twist_leader_frigo_2_flag    = ON;							// フラグチェック
		twist_leader_umrs2009_1_flag = ON;							// フラグチェック
		twist_leader_umrs2009_2_flag = ON;							// フラグチェック
		twist_leader_umrs2010_1_flag = ON;							// フラグチェック
		twist_leader_umrs2010_2_flag = ON;							// フラグチェック

	}else if(joy->axes[1] < init_data.down_threshold){						// ジョイスティック左の下チェック

		twist_leader_kohga3_1.twist.linear.x
			= init_data.backward_maximum_velocity * (init_data.down_threshold - joy->axes[1])
			/ (1.0 + init_data.down_threshold);						// 速度ベクトルx成分格納
		twist_leader_kohga3_1_flag   = ON;							// フラグチェック
		twist_leader_kohga3_2_flag   = ON;							// フラグチェック
		twist_leader_frigo_1_flag    = ON;							// フラグチェック
		twist_leader_frigo_2_flag    = ON;							// フラグチェック
		twist_leader_umrs2009_1_flag = ON;							// フラグチェック
		twist_leader_umrs2009_2_flag = ON;							// フラグチェック
		twist_leader_umrs2010_1_flag = ON;							// フラグチェック
		twist_leader_umrs2010_2_flag = ON;							// フラグチェック

	}else{												// ジョイスティック左の不感帯チェック

		twist_leader_kohga3_1.twist.linear.x = 0.0;						// 速度ベクトルx成分格納
		twist_leader_kohga3_1_flag           = ON;						// フラグチェック
		twist_leader_kohga3_2_flag           = ON;						// フラグチェック
		twist_leader_frigo_1_flag            = ON;						// フラグチェック
		twist_leader_frigo_2_flag            = ON;						// フラグチェック
		twist_leader_umrs2009_1_flag         = ON;						// フラグチェック
		twist_leader_umrs2009_2_flag         = ON;						// フラグチェック
		twist_leader_umrs2010_1_flag         = ON;						// フラグチェック
		twist_leader_umrs2010_2_flag         = ON;						// フラグチェック

	}

	// ジョイスティック左の左右処理
	if(joy->axes[0] > init_data.left_threshold){							// ジョイスティック左の左チェック

		twist_leader_kohga3_1.twist.angular.z
			= init_data.ccw_maximum_angular_velocity * (joy->axes[0] - init_data.left_threshold)
			/ (1.0 - init_data.left_threshold);						// 角速度ベクトルz成分格納
		twist_leader_kohga3_1_flag   = ON;							// フラグチェック
		twist_leader_kohga3_2_flag   = ON;							// フラグチェック
		twist_leader_frigo_1_flag    = ON;							// フラグチェック
		twist_leader_frigo_2_flag    = ON;							// フラグチェック
		twist_leader_umrs2009_1_flag = ON;							// フラグチェック
		twist_leader_umrs2009_2_flag = ON;							// フラグチェック
		twist_leader_umrs2010_1_flag = ON;							// フラグチェック
		twist_leader_umrs2010_2_flag = ON;							// フラグチェック

	}else if(joy->axes[0] < init_data.right_threshold){						// ジョイスティック左の右チェック

		twist_leader_kohga3_1.twist.angular.z
			= init_data.cw_maximum_angular_velocity * (init_data.right_threshold - joy->axes[0])
			/ (1.0 + init_data.right_threshold);						// 角速度ベクトルz成分格納
		twist_leader_kohga3_1_flag   = ON;							// フラグチェック
		twist_leader_kohga3_2_flag   = ON;							// フラグチェック
		twist_leader_frigo_1_flag    = ON;							// フラグチェック
		twist_leader_frigo_2_flag    = ON;							// フラグチェック
		twist_leader_umrs2009_1_flag = ON;							// フラグチェック
		twist_leader_umrs2009_2_flag = ON;							// フラグチェック
		twist_leader_umrs2010_1_flag = ON;							// フラグチェック
		twist_leader_umrs2010_2_flag = ON;							// フラグチェック

	}else{												// ジョイスティック左の不感帯チェック

		twist_leader_kohga3_1.twist.angular.z = 0.0;						// 角速度ベクトルz成分格納
		twist_leader_kohga3_1_flag            = ON;						// フラグチェック
		twist_leader_kohga3_2_flag            = ON;						// フラグチェック
		twist_leader_frigo_1_flag             = ON;						// フラグチェック
		twist_leader_frigo_2_flag             = ON;						// フラグチェック
		twist_leader_umrs2009_1_flag          = ON;						// フラグチェック
		twist_leader_umrs2009_2_flag          = ON;						// フラグチェック
		twist_leader_umrs2010_1_flag          = ON;						// フラグチェック
		twist_leader_umrs2010_2_flag          = ON;						// フラグチェック

	}

	// メッセージ複製処理
	twist_leader_kohga3_2.header.stamp      = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_kohga3_2.header.frame_id   = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_kohga3_2.twist.linear.x    = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_kohga3_2.twist.angular.z   = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_frigo_1.header.stamp       = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_frigo_1.header.frame_id    = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_frigo_1.twist.linear.x     = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_frigo_1.twist.angular.z    = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_frigo_2.header.stamp       = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_frigo_2.header.frame_id    = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_frigo_2.twist.linear.x     = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_frigo_2.twist.angular.z    = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_umrs2009_1.header.stamp    = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_umrs2009_1.header.frame_id = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_umrs2009_1.twist.linear.x  = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_umrs2009_1.twist.angular.z = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_umrs2009_2.header.stamp    = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_umrs2009_2.header.frame_id = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_umrs2009_2.twist.linear.x  = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_umrs2009_2.twist.angular.z = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_umrs2010_1.header.stamp    = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_umrs2010_1.header.frame_id = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_umrs2010_1.twist.linear.x  = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_umrs2010_1.twist.angular.z = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納
	twist_leader_umrs2010_2.header.stamp    = twist_leader_kohga3_1.header.stamp;			// タイムスタンプ格納
	twist_leader_umrs2010_2.header.frame_id = twist_leader_kohga3_1.header.frame_id;		// フレームID格納
	twist_leader_umrs2010_2.twist.linear.x  = twist_leader_kohga3_1.twist.linear.x;			// 速度ベクトルx成分格納
	twist_leader_umrs2010_2.twist.angular.z = twist_leader_kohga3_1.twist.angular.z;		// 角速度ベクトルz成分格納

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_KOHGA3_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 timestamp          ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_kohga3_1.header.stamp.sec,
		twist_leader_kohga3_1.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 frame id           ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_kohga3_1.header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 linear x           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 linear y           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 linear z           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 angular x          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 angular y          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_1 angular z          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_1.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_KOHGA3_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 timestamp          ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_kohga3_2.header.stamp.sec,
		twist_leader_kohga3_2.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 frame id           ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_kohga3_2.header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 linear x           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 linear y           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 linear z           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 angular x          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 angular y          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_kohga3_2 angular z          ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_kohga3_2.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_FRIGO_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 timestamp           ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_frigo_1.header.stamp.sec,
		twist_leader_frigo_1.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 frame id            ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_frigo_1.header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 linear x            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 linear y            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 linear z            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 angular x           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 angular y           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_1 angular z           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_1.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_FRIGO_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 timestamp           ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_frigo_2.header.stamp.sec,
		twist_leader_frigo_2.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 frame id            ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_frigo_2.header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 linear x            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 linear y            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 linear z            ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 angular x           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 angular y           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_frigo_2 angular z           ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_frigo_2.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_UMRS2009_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 timestamp        ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_umrs2009_1.header.stamp.sec,
		twist_leader_umrs2009_1.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 frame id         ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_umrs2009_1.header.frame_id;						// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 linear x         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 linear y         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 linear z         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 angular x        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 angular y        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_1 angular z        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_1.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_UMRS2009_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 timestamp        ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_umrs2009_2.header.stamp.sec,
		twist_leader_umrs2009_2.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 frame id         ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_umrs2009_2.header.frame_id;						// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 linear x         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 linear y         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 linear z         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 angular x        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 angular y        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2009_2 angular z        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2009_2.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_UMRS2010_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 timestamp        ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_umrs2010_1.header.stamp.sec,
		twist_leader_umrs2010_1.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 frame id         ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_umrs2010_1.header.frame_id;						// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 linear x         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 linear y         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 linear z         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 angular x        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 angular y        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_1 angular z        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_1.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_TWIST_LEADER_UMRS2010_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 timestamp        ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", twist_leader_umrs2010_2.header.stamp.sec,
		twist_leader_umrs2010_2.header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 frame id         ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << twist_leader_umrs2010_2.header.frame_id;						// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 linear x         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.linear.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 linear y         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.linear.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 linear z         ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.linear.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 angular x        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.angular.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 angular y        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.angular.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ twist_leader_umrs2010_2 angular z        ]");						// メッセージ表示
	printf("[ %10.6f                               ]\n", twist_leader_umrs2010_2.twist.angular.z);	// メッセージ表示
	printf("\033[%dA", 8);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_kohga3_1_callback(const kyoto::RelativePoseStamped::ConstPtr&			-//
//-  position_kohga3_1)										-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_kohga3_1_callback(const kyoto::RelativePoseStamped::ConstPtr& position_kohga3_1)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_KOHGA3_1									// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 sequence number        ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_kohga3_1->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 timestamp              ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_kohga3_1->header.stamp.sec,
		position_kohga3_1->header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 frame id               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_kohga3_1->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 target                 ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_kohga3_1->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_kohga3_1->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 position x             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_1->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 position y             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_1->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 position z             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_1->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 orientation x          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_1->pose.orientation.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 orientation y          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_1->pose.orientation.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 orientation z          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_1->pose.orientation.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_1 orientation w          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_1->pose.orientation.w);	// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_kohga3_2_callback(const kyoto::RelativePoseStamped::ConstPtr&			-//
//-  position_kohga3_2)										-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_kohga3_2_callback(const kyoto::RelativePoseStamped::ConstPtr& position_kohga3_2)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_KOHGA3_2									// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 sequence number        ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_kohga3_2->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 timestamp              ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_kohga3_2->header.stamp.sec,
		position_kohga3_2->header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 frame id               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_kohga3_2->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 target                 ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_kohga3_2->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_kohga3_2->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 position x             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_2->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 position y             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_2->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 position z             ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_kohga3_2->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 orientation x          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_2->pose.orientation.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 orientation y          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_2->pose.orientation.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 orientation z          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_2->pose.orientation.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_kohga3_2 orientation w          ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_kohga3_2->pose.orientation.w);	// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_frigo_1_callback(const kyoto::RelativePoseStamped::ConstPtr&			-//
//-  position_frigo_1)										-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_frigo_1_callback(const kyoto::RelativePoseStamped::ConstPtr& position_frigo_1)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_FRIGO_1									// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 sequence number         ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_frigo_1->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 timestamp               ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_frigo_1->header.stamp.sec,
		position_frigo_1->header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 frame id                ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_frigo_1->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 target                  ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_frigo_1->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_frigo_1->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 position x              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_1->pose.position.x);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 position y              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_1->pose.position.y);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 position z              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_1->pose.position.z);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 orientation x           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_1->pose.orientation.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 orientation y           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_1->pose.orientation.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 orientation z           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_1->pose.orientation.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_1 orientation w           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_1->pose.orientation.w);	// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_frigo_2_callback(const kyoto::RelativePoseStamped::ConstPtr&			-//
//-  position_frigo_2)										-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_frigo_2_callback(const kyoto::RelativePoseStamped::ConstPtr& position_frigo_2)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_FRIGO_2									// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 sequence number         ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_frigo_2->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 timestamp               ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_frigo_2->header.stamp.sec,
		position_frigo_2->header.stamp.nsec);							// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 frame id                ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_frigo_2->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 target                  ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_frigo_2->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_frigo_2->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 position x              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_2->pose.position.x);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 position y              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_2->pose.position.y);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 position z              ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_frigo_2->pose.position.z);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 orientation x           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_2->pose.orientation.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 orientation y           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_2->pose.orientation.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 orientation z           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_2->pose.orientation.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_frigo_2 orientation w           ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n", position_frigo_2->pose.orientation.w);	// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_umrs2009_1_callback(const kyoto::RelativePoseStamped::ConstPtr&		-//
//-  position_umrs2009_1)									-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_umrs2009_1_callback(const kyoto::RelativePoseStamped::ConstPtr& position_umrs2009_1)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_UMRS2009_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 sequence number      ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_umrs2009_1->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 timestamp            ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_umrs2009_1->header.stamp.sec,
		position_umrs2009_1->header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 frame id             ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2009_1->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 target               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2009_1->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_umrs2009_1->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 position x           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_1->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 position y           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_1->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 position z           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_1->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 orientation x        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_1->pose.orientation.x);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 orientation y        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_1->pose.orientation.y);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 orientation z        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_1->pose.orientation.z);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_1 orientation w        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_1->pose.orientation.w);						// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_umrs2009_2_callback(const kyoto::RelativePoseStamped::ConstPtr&		-//
//-  position_umrs2009_2)									-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_umrs2009_2_callback(const kyoto::RelativePoseStamped::ConstPtr& position_umrs2009_2)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_UMRS2009_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 sequence number      ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_umrs2009_2->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 timestamp            ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_umrs2009_2->header.stamp.sec,
		position_umrs2009_2->header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 frame id             ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2009_2->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 target               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2009_2->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_umrs2009_2->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 position x           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_2->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 position y           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_2->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 position z           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2009_2->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 orientation x        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_2->pose.orientation.x);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 orientation y        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_2->pose.orientation.y);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 orientation z        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_2->pose.orientation.z);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2009_2 orientation w        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2009_2->pose.orientation.w);						// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_umrs2010_1_callback(const kyoto::RelativePoseStamped::ConstPtr&		-//
//-  position_umrs2010_1)									-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_umrs2010_1_callback(const kyoto::RelativePoseStamped::ConstPtr& position_umrs2010_1)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_UMRS2010_1								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 sequence number      ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_umrs2010_1->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 timestamp            ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_umrs2010_1->header.stamp.sec,
		position_umrs2010_1->header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 frame id             ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2010_1->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 target               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2010_1->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_umrs2010_1->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 position x           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_1->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 position y           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_1->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 position z           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_1->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 orientation x        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_1->pose.orientation.x);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 orientation y        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_1->pose.orientation.y);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 orientation z        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_1->pose.orientation.z);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_1 orientation w        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_1->pose.orientation.w);						// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//


//-- [コールバック関数] -------------------------------------------------------------------------//
//- void position_umrs2010_2_callback(const kyoto::RelativePoseStamped::ConstPtr&		-//
//-  position_umrs2010_2)									-//
//- 機能   : コールバック処理を行う [kyoto/RelativePoseStamped]					-//
//- 引数   : (const kyoto::RelativePoseStamped::ConstPtr&) 更新メッセージアドレス		-//
//- 戻り値 : (void)                                        なし					-//
//-----------------------------------------------------------------------------------------------//
void position_umrs2010_2_callback(const kyoto::RelativePoseStamped::ConstPtr& position_umrs2010_2)
{

	//-- [名前空間指定] ---------------------------------------------------------------------//

	using std::cout;										// std::cout指定

	//---------------------------------------------------------------------------------------//


	//-- [変数宣言] -------------------------------------------------------------------------//

	// プログラム処理
	int i;												// カウンタ格納変数

	//---------------------------------------------------------------------------------------//


	//-- [デバッグ処理] ---------------------------------------------------------------------//

	#ifndef DEBUG_POSITION_UMRS2010_2								// デバッグ実行設定開始
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 sequence number      ]");						// メッセージ表示
	printf("[ %010d                               ]\n", position_umrs2010_2->header.seq);		// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 timestamp            ]");						// メッセージ表示
	printf("[ %10d.%09d                     ]\n", position_umrs2010_2->header.stamp.sec,
		position_umrs2010_2->header.stamp.nsec);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 frame id             ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2010_2->header.frame_id;							// メッセージ表示
	printf("\"                                       ]\n");						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 target               ]");						// メッセージ表示
	printf("[ \"");											// メッセージ表示
	cout << position_umrs2010_2->target;								// メッセージ表示
	printf("\"");											// メッセージ表示
	for(i = 0; i < (39 - position_umrs2010_2->target.length()); i++) printf(" ");			// メッセージ表示
	printf("]\n");											// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 position x           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_2->pose.position.x);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 position y           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_2->pose.position.y);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 position z           ]");						// メッセージ表示
	printf("[ %11.1f                              ]\n", position_umrs2010_2->pose.position.z);	// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 orientation x        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_2->pose.orientation.x);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 orientation y        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_2->pose.orientation.y);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 orientation z        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_2->pose.orientation.z);						// メッセージ表示
	printf("[ kyoto/formation           ]");							// メッセージ表示
	printf("[ position_umrs2010_2 orientation w        ]");						// メッセージ表示
	printf("[ %6.4f                                   ]\n",
		position_umrs2010_2->pose.orientation.w);						// メッセージ表示
	printf("\033[%dA", 11);										// メッセージ表示
	fflush(stdout);											// バッファフラッシュ [printf表示]
	#endif												// デバッグ実行設定終了

	//---------------------------------------------------------------------------------------//


	return;												// 戻り値 [正常終了]

}
//-----------------------------------------------------------------------------------------------//
