#include "statethreadbase.h"

StateThreadBase::StateThreadBase(QObject *parent)
    : QThread(parent)
    , strState(tr(""))
    , strStateExtra(tr(""))
    , state(StateThreadBase::OK)
{

}

void StateThreadBase::translateState()
{
    switch(state) {
    case OK:
        strState = tr("成功");
        break;
    case WRONG_PASS:
        strState = tr("密码错误");
        break;
    case MISMATCH_PASS:
        strState = tr("两次密码不匹配");
        break;
    case CHANGE_PASS_FAILED:
        strState = tr("设置密码失败");
        break;
    case MOUNT_PART_FAILED:
        strState = tr("装载分区失败");
        break;
    case UNMOUNT_PART_FAILED:
        strState = tr("卸载分区失败");
        break;
    case MOUNT_IMAGE_FAILED:
        strState = tr("装载镜像失败");
        break;
    case UNMOUNT_IMAGE_FAILED:
        strState = tr("卸载镜像失败");
        break;
    case MOUNT_SERIAL_FAILED:
        strState = tr("连接串口失败");
        break;
    case UNMOUNT_SERIAL_FAILED:
        strState = tr("断开串口失败");
        break;
    case MOUNT_NIC_FAILED:
        strState = tr("模拟网卡失败");
        break;
    case UNMOUNT_NIC_FAILED:
        strState = tr("断开网卡失败");
        break;
    case SYSTEM_ERROR:
        strState = tr("系统错误");
        break;
    case UNKNOWN_FAILED:
        strState = tr("未知");
    }
}
