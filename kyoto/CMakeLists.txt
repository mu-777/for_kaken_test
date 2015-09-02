#-- [CMake設定] ---------------------------------------------------------------------------------#

# CMakeバージョン
cmake_minimum_required(VERSION 2.8.3)

#------------------------------------------------------------------------------------------------#


#-- [パッケージ設定] ----------------------------------------------------------------------------#

# パッケージ名
project(kyoto)

# 依存CMakeパッケージ
# catkin			: ROSビルドシステムマクロパッケージ
# message_generation		: メッセージ生成パッケージ
# roscpp			: C++言語ライブラリパッケージ
# rospy				: Python言語ライブラリパッケージ
# std_msgs			: 標準メッセージパッケージ
# geometry_msgs			: 幾何学メッセージパッケージ
# nav_msgs			: ロボットナビゲーションメッセージパッケージ
# sensor_msgs			: センサメッセージパッケージ
find_package(			catkin REQUIRED COMPONENTS
				message_generation
				roscpp
				rospy
				std_msgs
				geometry_msgs
				nav_msgs
				sensor_msgs)

#------------------------------------------------------------------------------------------------#


#-- [メッセージ設定] ----------------------------------------------------------------------------#

# メッセージ処理マクロ
# SelectStamped.msg		: 自作メッセージ
# RelativePoseStamped.msg	: 自作メッセージ
add_message_files(		FILES
				SelectStamped.msg
				RelativePoseStamped.msg)
	
# メッセージ生成マクロ
# std_msgs			: 標準メッセージパッケージ
# geometry_msgs			: 幾何学メッセージパッケージ
# nav_msgs			: ロボットナビゲーションメッセージパッケージ
# sensor_msgs			: センサメッセージパッケージ
generate_messages(		DEPENDENCIES
				std_msgs
				geometry_msgs
				nav_msgs
				sensor_msgs)

#------------------------------------------------------------------------------------------------#


#-- [コンパイル設定] ----------------------------------------------------------------------------#

# CMakeマクロ
catkin_package()

# 挿入デレクトリ
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

# 実行ファイルターゲット
add_executable(formation src/formation/main.cpp src/formation/formation.cpp)
add_executable(encoder_kohga3_1 src/encoder_kohga3_1/main.cpp src/encoder_kohga3_1/encoder_kohga3_1.cpp)
add_executable(encoder_kohga3_2 src/encoder_kohga3_2/main.cpp src/encoder_kohga3_2/encoder_kohga3_2.cpp)
add_executable(decoder_kohga3_1 src/decoder_kohga3_1/main.cpp src/decoder_kohga3_1/decoder_kohga3_1.cpp)
add_executable(decoder_kohga3_2 src/decoder_kohga3_2/main.cpp src/decoder_kohga3_2/decoder_kohga3_2.cpp)

# ライブラリターゲット
target_link_libraries(formation ${catkin_LIBRARIES})
target_link_libraries(encoder_kohga3_1 ${catkin_LIBRARIES})
target_link_libraries(encoder_kohga3_2 ${catkin_LIBRARIES})
target_link_libraries(decoder_kohga3_1 ${catkin_LIBRARIES})
target_link_libraries(decoder_kohga3_2 ${catkin_LIBRARIES})

# メッセージターゲット
add_dependencies(formation ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(encoder_kohga3_1 ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(encoder_kohga3_2 ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(decoder_kohga3_1 ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(decoder_kohga3_2 ${PROJECT_NAME}_generate_messages_cpp)

#------------------------------------------------------------------------------------------------#
