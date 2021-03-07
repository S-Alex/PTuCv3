//;File: "MenuHAL.h"
//;Updated: "2010-09-02" "21:19"
//;Updated: "2011-01-04" "00:14"
//
#ifndef INCLUDE_MENUHAL
#define INCLUDE_MENUHAL

#include  "main.h"
#include  "Sets.h"

#define UC_DEG 0

//#define USE_MT_SUB

extern u08 v_LED3Buf[];

//; ����. ������ 0.0
//; �����������. ����� ���������� ��� ���� ������� ����.
//#define MT_NUM 0  // �������� ��������. ����� �������� 16���
//#define MT_LST 1  // ������ ��������� ��������. ��������: "���."; "����."
//#define MT_SUB 2  // �������. ��������: "���. ���������"; "���. ���������";

/** �������� ������� ���� #MenuType � ��������� #Ctrl_t

*/
typedef enum {
  MT_UNUM8,   /**< �������� ��������. ����� �������� 8��� */
  MT_UNUM,    /**< �������� ��������. ����� �������� 16��� */
  MT_SNUM,    /**< �������� ��������. ����� �������� 16���  */
//  MT_LST,     /**< ������ ��������� ��������. ��������: "���."; "����." */
  MT_BUTTON,  /**< ������;          */
  MT_SUB,     /**< �������. ��������: "���. ���������"; "���. ���������"; */
//  MT_LST_RAM,  /**< ������ ��������� ��������. ��������: "���."; "����." */
//  MT_STR  /**< ������ ��������� ��������. ��������: "���."; "����." */
} eMENU_TYPE_t;

//; |0123456789012345|
//; +----------------+
//; |AGRIATIS PTCv1.0|
//; |                |
//; +----------------+
//
//; |0123456789012345|
//; +----------------+
//; | 85C  25C  2015�| ����� �������
//; |18:00:00�� 11���|
//; +----------------+


//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | ����      2015�| ��������� ����
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | ������    2015�| ��������� �����
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | �������   2015�| ��������� ������
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | ����      2015�| ��������� ��� ������
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | �����     2015�| ��������� ������
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; | ���       2015�| ��������� ����
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; |�������    2015�| ������ ��������� � �������
//; |18:00:00�� 11���|
//; +----------------+

//; |0123456789012345|
//; +----------------+ ����� ��������� �������
//; |���������  2015�| ��������� ���������
//; |18:00:00�� 11���|
//; +----------------+

typedef enum {
  MSG_NOT,  //;
  MSG_DRAW, /**< ��������� ��������� ���� */
  MSG_DRAWDATE, /**< ��������� ��������� ���� ���� */
  MSG_NEXT, /**< ��������� ������� �� ��������� ����� ����  */
  MSG_PREV, /**< ��������� ������� �� ���������� ����� ���� */

  MSG_SWDN,  /**< ��������� ������ �������� ������. */
  MSG_SWUP,  /**< ��������� ������ �������� ��������. */

  MSG_PARAM_INC,  /**< ��������� ��������� �������� ��������� �� 1. */
  MSG_PARAM_DEC,  /**< ��������� ��������� �������� ��������� �� 1. */

  MSG_SELECT,     /**< ��������� ������ �������� ������ ����. */
  MSG_RETURN,     /**< ��������� ������� �� �������. */

} eMENU_MSG_t;






extern u08   v_InputLast;  //(-1; 0; +1) ; ��� ����������� � ���������.
//extern uint16_t  v_InValInit;  //��������� ������� v_InputVal
//extern uint16_t  v_InVal    ;  //(-xx; 0; +xx) ; ����� �� ������� ����� �������� ��������
extern u08   v_MenuReCnt;  //���������� �������� �������� � ����� �����������.


typedef struct {
  const u08 __flash  *pszItemMenu;  /**< ��������� �� ASCIIZ ������, ����� ���������� ������ ���� */
//  u08   x_szItemMenu; /**<���������� x ������ ������ ������ ���� */
//  u08   y_szItemMenu; /**<���������� y ������ ������ ������ ���� */
  eMENU_TYPE_t MenuType; /**<��� ���� MT_NUM; MT_LST; MT_SUB; MT_BUTTON */
  //    ;   MT_NUM  ; �������� ��������. ����� �������� 16 ���
  //    ;   MT_LST  ; ������ ��������� ��������. ��������: "���."; "����."
  //    ;   MT_SUB  ; �������. ��������: "���. ���������"; "���. ���������";
  union uParam {
    u08  *u08Val;    /**<��������� �� �������� ������ ���� (������ RAM 16bit) */
    u16  *u16Val;    /**<��������� �� �������� ������ ���� (������ RAM 16bit) */
    s16  *s16Val;    /**<��������� �� �������� ������ ���� (������ RAM 16bit) */
    Timer_t *pTimer;    /**<��������� �� �������� ������ ����  */
    u08 * const __flash *szStr;
  } pParam;
//  u08   x_ValParam;   /**< ���������� x ������ �������� ��������� ������ ���� */
//  u08   y_ValParam;   /**< ���������� � ������ �������� ��������� ������ ���� */
  union uExPrm1 {
    s16  s_Min;       /**< ����������� �������� ��������� */
    u16  u_Min;       /**< ����������� �������� ��������� */
    //    ; MT_NUM -> ����������� �������� ���������
    //    ; MT_SUB ->
    const u08 __flash *const __flash *ppszListItem; /**��������� �� ��������� ����� ��� ������ MT_LST */
    u08 *const __flash * ppszListItem_RAM; /**��������� �� ��������� ����� ��� ������ MT_LST */
    //    ; MT_LST ->
    u08 BtnDnTaskID;   /**< ID ������ ��������� ������� ������ */
    u08 nTimer;   /**< ����� ������� */

  } ExPrm1;
  union uExPrm2 {
    s16 s_Max;        /**< ������������ �������� ���������  */
    u16 u_Max;        /**< ������������ �������� ���������  */
    //    ; MT_NUM ->
    u16 *hSubMenu;    /**< ��������� �� ������� */
    //    ; MT_SUB -> SubMenuID. ������������� �������.
    u08   nLst;
    //    ; MT_LST -> ����� ����� ������ ��� ������.
    u08 BtnUpTaskID;   /**< ID ������ ��������� ���������� ������ */\
  } ExPrm2;
  //  void (*pFuncMenu)(void) ;/**<��������� �� ������� ������� ������������ ������ ����� ���� */
  u08 TaskID;         /**< ID ������ ��������� ���� */\
//  char   Unit;        /**< ������� ��������� ��������� */
} Ctrl_t;

typedef enum {
  IDLE,
  NORMAL,
  EDIT,
//  EXEDIT,
//  SAVE,
} eMODE_t;



typedef struct {
  const Ctrl_t __flash(*const __flash *hMenu)[];    //  ��������� �� ������� ����
  u08 C_Indx;
  eMENU_MSG_t Msg   ;   //��������� ��� ������ ��������� ����
  u08 TaskID;   //ID ������ ��������� ����
  eMODE_t  vMode;/* ������� ����� ������. 0 - ����������; 1 - ����������������. */
  //  u08 LstItem:  5; /* ����� ������� ��� ���� ���� MT_LST*/
  //  /* ��� ������ ����� ���� �� ������������ */
  //
  //  u08 Type:     3; /* ����� ������� ��� ���� ���� MT_LST*/
  //  /* MT_NUM  �������� ��������. ����� �������� 16��� */
  //  /* MT_LST  ������ ��������� ��������. ��������: "���."; "����." */
  //  /* MT_SUB  �������. ��������: "���. ���������"; "���. ���������"; */
  //  u08 NextID;   //ID ���������� ������ ����
  //  u08 PrevID;   //ID ����������� ������ ����
  //  u08 CurID ;   //ID �������� ������ ����
  //
  //  u08 IDCurM;   //  ���������� ����� ��������� ������ �������� ����.
} Menu_t;


//{ ���� ����
u08 MenuSP;   //  ��������� ����� ��� ID ������� ����
struct sMenuStk {
  Ctrl_t**hMenu;
  u08 C_Indx;
} MenuStk[4];//  ���� ��� ID ������� ���� ��� �������� �� �������. ��� ���� ���� MT_SUB
//} ���� ����


extern  Menu_t v_Menu;
extern  eMODE_t vMode;    /* ������� ����� ������. 0 - ����������; 1 - ����������������. */
extern u08 * const __flash Lst_nSets_Ram[];



void fMenuInit(void);

void fMenuSendMsg(eMENU_MSG_t Menu_Msg);

void fMenuDraw(void);
void fMenuNext(void);
void fMenuPrev(void);
void fMenuSelect(void);
void fMenuDefProc(void);
void fMenuParamIncDec(void);
void fMenuButtonProc(void);


/**


*/
void fMenuDrawTime(void);
void fMenuDefEditProc(void);


void fMenuSubDefProc(void);

void fMenuSubSelectProc(void);

const Ctrl_t __flash *fMenuGetHndCtrl(void);

void fMenuDrawCtrl(void);
void fMenuDraw_szItemMenu(const Ctrl_t __flash *pCtrl);

u08 fGetIncDecVal(u08 CntIncDec);
void fMenuIncDecTime(void);
void f_SetsAtTimePrint(u08 nTimer);

void fMenuProcTimer(void);


#endif // INCLUDE_MENUHAL

//;S_Alex