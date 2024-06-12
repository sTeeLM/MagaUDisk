#include "statethreadbase.h"

StateThreadBase::StateThreadBase(QObject *parent)
    : QThread(parent)
    , strState("")
    , strStateExtra("")
    , state(StateThreadBase::OK)
{

}

void StateThreadBase::translateState()
{
    switch(state) {
    case OK:
        strState = "成功";
        break;
    case WRONG_PASS:
        strState = "密码错误";
        break;
    case CHANGE_PASS_FAILED:
        strState = "设置密码失败";
        break;
    case MOUNT_PART_FAILED:
        strState = "装载分区失败";
        break;
    case UNMOUNT_PART_FAILED:
        strState = "卸载分区失败";
        break;
    case MOUNT_IMAGE_FAILED:
        strState = "装载镜像失败";
        break;
    case UNMOUNT_IMAGE_FAILED:
        strState = "卸载镜像失败";
        break;
    case MOUNT_SERIAL_FAILED:
        strState = "连接串口失败";
        break;
    case UNMOUNT_SERIAL_FAILED:
        strState = "断开串口失败";
        break;
    case MOUNT_NIC_FAILED:
        strState = "模拟网卡失败";
        break;
    case UNMOUNT_NIC_FAILED:
        strState = "断开网卡失败";
        break;
    case SYSTEM_ERROR:
        strState = "系统错误";
        break;
    case UNKNOWN_FAILED:
        strState = "未知";
    }
}
