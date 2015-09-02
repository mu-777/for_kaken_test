//***********************************************************************************************//
//* formation.h									     2015/08/22 *//
//*												*//
//* 関数 :											*//
//*  メッセージ表示関数      -> void message_display(unsigned int)				*//
//*  INIファイル読み込み関数 -> int ini_file_read(char *, struct Initialization *)		*//
//*												*//
//*								(c) HAREHIME 2015 NITYC H.MAEDA *//
//***********************************************************************************************//

//-- [ヘッダファイル二重読み込み防止処理] -------------------------------------------------------//
#ifndef __FORMATION__											// 条件コンパイル開始
#define __FORMATION__											// 条件判断用定義セット
//-----------------------------------------------------------------------------------------------//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
//- geometry_msgs/TwistStamped.h : geometry_msgs::TwistStamped					-//
//- kyoto/RelativePoseStamped.h  : kyoto::RelativePoseStamped					-//
//- kyoto/SelectStamped.h        : kyoto::SelectStamped						-//
//- sensor_msgs/Joy.h            : sensor_msgs::Joy						-//
//- stdio.h                      : fclose, fflush, fgets, fopen, printf				-//
//- stdlib.h                     : atof, exit							-//
//- string.h                     : strlen, strstr						-//
//- ros/ros.h                    : ros::init, ros::ok, ros::spinOnce, ros::NodeHandle,		-//
//-                                ros::Publisher, ros::Rate, ros::Subscriber, ros::Time	-//
//- sys/time.h                   : time								-//
//-----------------------------------------------------------------------------------------------//
#include <geometry_msgs/TwistStamped.h>									// geometry_msgs/TwistStamped
													//  ヘッダファイル読み込み
#include <kyoto/RelativePoseStamped.h>									// kyoto/RelativePoseStamped
													//  ヘッダファイル読み込み
#include <kyoto/SelectStamped.h>									// kyoto/SelectStamped
													//  ヘッダファイル読み込み
#include <sensor_msgs/Joy.h>										// sensor_msgs/Joy
													//  ヘッダファイル読み込み
#include <stdio.h>											// stdioヘッダファイル読み込み
#include <stdlib.h>											// stdlibヘッダファイル読み込み
#include <string.h>											// stringヘッダファイル読み込み
#include <ros/ros.h>											// ros/rosヘッダファイル読み込み
#include <sys/time.h>											// sys/timeヘッダファイル読み込み
//-----------------------------------------------------------------------------------------------//


//-- [置換] -------------------------------------------------------------------------------------//
//- SUCCESS                            : 0							-//
//- FAILURE                            : - 1							-//
//- ON                                 : 1							-//
//- OFF                                : 0							-//
//- PROGRAM_BEGINNING                  : 0							-//
//- PROGRAM_END                        : 1							-//
//- INITIALIZATION_BEGINNING           : 2							-//
//- INITIALIZATION_END                 : 3							-//
//- THE_MAIN_PROGRAM_BEGINNING         : 4							-//
//- THE_MAIN_PROGRAM_END               : 5							-//
//- FILE_OPEN_FAILURE                  : 6							-//
//- ROS                                : 7							-//
//- LINE_SIZE                          : 256							-//
//- INI_FILE_NAME                      : "./initialization/formation.ini"			-//
//- JOY_UP_THRESHOLD                   : "UpThreshold="						-//
//- JOY_DOWN_THRESHOLD                 : "DownThreshold="					-//
//- JOY_LEFT_THRESHOLD                 : "LeftThreshold="					-//
//- JOY_RIGHT_THRESHOLD                : "RightThreshold="					-//
//- TWIST_FORWARD_MAXIMUM_VELOCITY     : "ForwardMaximumVelocity="				-//
//- TWIST_BACKWARD_MAXIMUM_VELOCITY    : "BackwardMaximumVelocity="				-//
//- TWIST_CCW_MAXIMUM_ANGULAR_VELOCITY : "CcwMaximumAngularVelocity="				-//
//- TWIST_CW_MAXIMUM_ANGULAR_VELOCITY  : "CwMaximumAngularVelocity="				-//
//- FORWARD_MAXIMUM_VELOCITY           : 1.388889						-//
//- BACKWARD_MAXIMUM_VELOCITY          : - 1.388889						-//
//- CCW_MAXIMUM_ANGULAR_VELOCITY       : 1.570796						-//
//- CW_MAXIMUM_ANGULAR_VELOCITY        : - 1.570796						-//
//- UP_THRESHOLD                       : 0.050000						-//
//- DOWN_THRESHOLD                     : - 0.050000						-//
//- LEFT_THRESHOLD                     : 0.050000						-//
//- RIGHT_THRESHOLD                    : - 0.050000						-//
//-----------------------------------------------------------------------------------------------//
#define SUCCESS					0							// 成功
#define FAILURE					- 1							// 失敗
#define ON					1							// ON
#define OFF					0							// OFF
#define PROGRAM_BEGINNING			0							// メッセージ番号0
#define PROGRAM_END				1							// メッセージ番号1
#define INITIALIZATION_BEGINNING		2							// メッセージ番号2
#define INITIALIZATION_END			3							// メッセージ番号3
#define THE_MAIN_PROGRAM_BEGINNING		4							// メッセージ番号4
#define THE_MAIN_PROGRAM_END			5							// メッセージ番号5
#define FILE_OPEN_FAILURE			6							// メッセージ番号6
#define ROS					7							// メッセージ番号7
#define LINE_SIZE				256							// 1行データサイズ
#define INI_FILE_NAME				"./initialization/formation.ini"			// INIファイル名
#define JOY_UP_THRESHOLD			"UpThreshold="						// 上不感帯閾値 [ ]
#define JOY_DOWN_THRESHOLD			"DownThreshold="					// 下不感帯閾値 [ ]
#define JOY_LEFT_THRESHOLD			"LeftThreshold="					// 左不感帯閾値 [ ]
#define JOY_RIGHT_THRESHOLD			"RightThreshold="					// 右不感帯閾値 [ ]
#define TWIST_FORWARD_MAXIMUM_VELOCITY		"ForwardMaximumVelocity="				// 前進最高速度 [m/sec]
#define TWIST_BACKWARD_MAXIMUM_VELOCITY		"BackwardMaximumVelocity="				// 後進最高速度 [m/sec]
#define TWIST_CCW_MAXIMUM_ANGULAR_VELOCITY	"CcwMaximumAngularVelocity="				// 左旋回最大角速度 [rad/sec]
#define TWIST_CW_MAXIMUM_ANGULAR_VELOCITY	"CwMaximumAngularVelocity="				// 右旋回最大角速度 [rad/sec]
//-----------------------------------------------------------------------------------------------//


//-- [型宣言] -----------------------------------------------------------------------------------//
typedef struct Initialization{										// 初期化データ格納構造体

	float up_threshold;										// 上不感帯閾値格納変数
	float down_threshold;										// 下不感帯閾値格納変数
	float left_threshold;										// 左不感帯閾値格納変数
	float right_threshold;										// 右不感帯閾値格納変数
	float forward_maximum_velocity;									// 前進最高速度格納変数
	float backward_maximum_velocity;								// 後進最高速度格納変数
	float ccw_maximum_angular_velocity;								// 左旋回最大角速度格納変数
	float cw_maximum_angular_velocity;								// 右旋回最大角速度格納変数

}Initialization;
//-----------------------------------------------------------------------------------------------//


//-- [プロトタイプ宣言] -------------------------------------------------------------------------//
void message_display(unsigned int);									// メッセージ表示関数
int ini_file_read(char *, struct Initialization *);							// INIファイル読み込み関数
//-----------------------------------------------------------------------------------------------//


//-- [ヘッダファイル末尾] -----------------------------------------------------------------------//
#endif													// 条件コンパイル終了
//-----------------------------------------------------------------------------------------------//
