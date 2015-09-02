//***********************************************************************************************//
//* encoder_kohga3_2.h								     2015/06/22 *//
//*												*//
//* 関数 :											*//
//*  メッセージ表示関数 -> void message_display(unsigned int)					*//
//*												*//
//*								(c) HAREHIME 2015 NITYC H.MAEDA *//
//***********************************************************************************************//

//-- [ヘッダファイル二重読み込み防止処理] -------------------------------------------------------//
#ifndef __ENCODER_KOHGA3_2__										// 条件コンパイル開始
#define __ENCODER_KOHGA3_2__										// 条件判断用定義セット
//-----------------------------------------------------------------------------------------------//


//-- [ヘッダファイル] ---------------------------------------------------------------------------//
//- geometry_msgs/TwistStamped.h : geometry_msgs::TwistStamped					-//
//- stdio.h                      : fflush, printf						-//
//- string                       : std::string							-//
//- ros/ros.h                    : ros::init, ros::ok, ros::NodeHandle, ros::Publisher,		-//
//-                                ros::Rate, ros::Time::now					-//
//- sys/time.h                   : time								-//
//-----------------------------------------------------------------------------------------------//
#include <geometry_msgs/TwistStamped.h>									// geometry_msgs/TwistStamped
													//  ヘッダファイル読み込み
#include <stdio.h>											// stdioヘッダファイル読み込み
#include <string>											// stringファイル読み込み
#include <ros/ros.h>											// ros/rosヘッダファイル読み込み
#include <sys/time.h>											// sys/timeヘッダファイル読み込み
//-----------------------------------------------------------------------------------------------//


//-- [置換] -------------------------------------------------------------------------------------//
//- SUCCESS                    : 0								-//
//- FAILURE                    : - 1								-//
//- ON                         : 1								-//
//- OFF                        : 0								-//
//- PROGRAM_BEGINNING          : 0								-//
//- PROGRAM_END                : 1								-//
//- INITIALIZATION_BEGINNING   : 2								-//
//- INITIALIZATION_END         : 3								-//
//- THE_MAIN_PROGRAM_BEGINNING : 4								-//
//- THE_MAIN_PROGRAM_END       : 5								-//
//- ROS                        : 6								-//
//-----------------------------------------------------------------------------------------------//
#define SUCCESS				0								// 成功
#define FAILURE				- 1								// 失敗
#define ON				1								// ON
#define OFF				0								// OFF
#define PROGRAM_BEGINNING		0								// メッセージ番号0
#define PROGRAM_END			1								// メッセージ番号1
#define INITIALIZATION_BEGINNING	2								// メッセージ番号2
#define INITIALIZATION_END		3								// メッセージ番号3
#define THE_MAIN_PROGRAM_BEGINNING	4								// メッセージ番号4
#define THE_MAIN_PROGRAM_END		5								// メッセージ番号5
#define ROS				6								// メッセージ番号6
//-----------------------------------------------------------------------------------------------//


//-- [プロトタイプ宣言] -------------------------------------------------------------------------//
void message_display(unsigned int);									// メッセージ表示関数
//-----------------------------------------------------------------------------------------------//


//-- [ヘッダファイル末尾] -----------------------------------------------------------------------//
#endif													// 条件コンパイル終了
//-----------------------------------------------------------------------------------------------//
