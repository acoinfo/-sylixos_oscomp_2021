/*********************************************************************************************************
**
**                                    �й������Դ��֯
**
**                                   Ƕ��ʽʵʱ����ϵͳ
**
**                                SylixOS(TM)  LW : long wing
**
**                               Copyright All Rights Reserved
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**
** ��   ��   ��: tmCmd.c
**
** ��   ��   ��: xxx
**
** �ļ���������: 2020 �� 12 �� 24 ��
**
** ��        ��: xxx ������
*********************************************************************************************************/
#define  __SYLIXOS_KERNEL
#include <SylixOS.h>
#include <stdio.h>

/*********************************************************************************************************
** ��������: tmEnable
** ��������: ʹ��ȥʹ������ͳ�ƹ���
** �䡡��  : bIsEnable   �Ƿ�ʹ��ͳ�ƹ���
** �䡡��  : NONE
** ������  : �������
*********************************************************************************************************/
INT  tmEnable (BOOL  bIsEnable)
{
    if (bIsEnable) {
        fprintf(stdout, "traffic statistics enable.\n");
    } else {
        fprintf(stdout, "traffic statistics disable.\n");
    }

    return 0;
}

/*********************************************************************************************************
** ��������: tmStatItemAdd
** ��������: ����������ͳ����
** �䡡��  : iArgC     �����в�������
**           ppcArgV   �����в�������
** �䡡��  : NONE
** ������  : �������
*********************************************************************************************************/
INT  tmStatItemAdd (INT  iArgC, PCHAR  *ppcArgV)
{
    fprintf(stdout, "traffic statistics add an item.\n");
    return 0;
}

/*********************************************************************************************************
** ��������: tmStatItemDelete
** ��������: ������ɾ��ͳ����
** �䡡��  : iArgC     �����в�������
**           ppcArgV   �����в�������
** �䡡��  : NONE
** ������  : �������
*********************************************************************************************************/
INT  tmStatItemDelete (INT  iArgC, PCHAR  *ppcArgV)
{
    fprintf(stdout, "traffic statistics delete an item.\n");
    return 0;
}

/*********************************************************************************************************
 ** ��������: tmShowStats
 ** ��������: ��ӡ����ͳ����Ϣ
 ** �䡡��  : iType     �����������ͣ�0 ��ʾ����, �������� TMT_*, �� TMT_TERM ��
 **           pip4Addr  �������� ip ��ַ
 ** �䡡��  : NONE
 ** ������  : NONE
*********************************************************************************************************/
VOID  tmShowStats (INT  iType, void  *pip4Addr)
{
    printf("Show traffic statistic:\n");

    printf("IP\t  ifname\t      MAC\t        TYPE\t  "
            "protocol\t port\t "
            "recv_curr_len\t send_curr_len\t recv_total_len(Bytes)\t"
            "send_total_len(Bytes) \n\n");

    //tmWalkStats(__tmPrintStatInfo, &iType, pip4Addr, LW_NULL);
}
/*********************************************************************************************************
** ��������: __tshellTmStat
** ��������: ���������������д�����
** �䡡��  : iArgC     �����в�������
**           ppcArgV   �����в�������
** �䡡��  : NONE
** ������  : NONE
*********************************************************************************************************/
static INT  __tshellTmStat (INT  iArgC, PCHAR  *ppcArgV)
{
    INT                 iType = 0;

    if (1 == iArgC) {
        tmShowStats(iType, LW_NULL);

        return  (ERROR_NONE);
    }

    if (!lib_strcmp(ppcArgV[1], "enable")) {
        tmEnable(LW_TRUE);
    } else if (!lib_strcmp(ppcArgV[1], "disable")) {
        tmEnable(LW_FALSE);
    } else if (!lib_strcmp(ppcArgV[1], "add")) {
        tmStatItemAdd(iArgC, ppcArgV);
    } else if (!lib_strcmp(ppcArgV[1], "del")) {
        tmStatItemDelete(iArgC, ppcArgV);
    } else if (!lib_strcmp(ppcArgV[1], "show")) {
        tmShowStats(iType, LW_NULL);
    } else {
        goto  __arg_error;
    }

    return  (ERROR_NONE);

__arg_error:
    fprintf(stderr, "arguments error!\n");

    return  (-ERROR_TSHELL_EPARAM);
}

/*********************************************************************************************************
** ��������: tmInstallCmd
** ��������: ��װ������
** �䡡��  : NONE
** �䡡��  : NONE
** ������  : NONE
*********************************************************************************************************/
VOID  tmInstallCmd (VOID)
{
    API_TShellKeywordAdd("tm", __tshellTmStat);
    API_TShellFormatAdd("tm", " add | del tm_type ip [mac] [ifname] [tcp | udp] [port]. \n"
                              "tm show [tm_type]. \n"
                              "tm disable | enable. \n");
    API_TShellHelpAdd("tm", "add, delete statistics item(tm_type should be one of term,line,app),\n"
                             " and show traffic statistics.\n"
                             "eg: tm add term 192.168.1.100 48:4d:7e:9f:bc:11\n"
                             "    tm add line en4 \n"
                             "    tm del line en4 \n"
                             "    tm del term 192.168.1.100 \n"
                             "    tm show term \n"
                             "    tm show line \n"
                             "    tm show app \n"
                             "    tm show lineapp \n"
                             "    tm disable \n");
}
