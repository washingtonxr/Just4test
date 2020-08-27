#include "L2Comm.h"
#include "L2AdaptComm.h"
/* line bi-direct list */
INT32 L2UdlPush(void *pHandle, void *pItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return L2_NOK;
    }
    if (NULL == pItem)
    {
        L2_UXM_E("err item!\n");
        return L2_NOK;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    L2UdlItem *pI = (L2UdlItem *)pItem;
    if (NULL == pH->pEnd)
    {
        pH->pBgn = pItem;
        pH->pEnd = pItem;
        pI->pNxt = NULL;
    }
    else
    {
        pI->pNxt = NULL;
        ((L2BdlItem *) (pH->pEnd))->pNxt = pItem;
        pH->pEnd = pItem;
    }
    return L2_OK;
}

void *L2UdlPull(void *pHandle)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return NULL;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    if (NULL == pH->pBgn)
    {
        return NULL;
    }
    L2UdlItem *pI = (L2UdlItem *) (pH->pBgn);
    if((pH->pBgn) == (pH->pEnd))
    {
        pH->pBgn = NULL;
        pH->pEnd = NULL;
    }
    else
    {
        pH->pBgn = pI->pNxt;
    }
    pI->pNxt = NULL;
    return pI;


}

void *L2UdlIter(void *pHandle, void *pPos)
{

    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return NULL;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    if((NULL == pH->pBgn) || (NULL == pH->pEnd)){
        L2_UXM_E("empty list!\n");
        return NULL;
    }    

    L2UdlItem *pP = (L2UdlItem *) pPos;
    if (NULL == pP)
    {
        return pH->pBgn;
    }
    else if (pH->pEnd == pP)
    {
        return NULL;
    }
    else
    {
        return pP->pNxt;
    }

}

/* line bi-direct array list */
INT32  L2UdalPush(void *pHandle, UINT32 iItem)
{

    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return L2_NOK;
    }

    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ( ((pH->iMax <= pH->iBgn) && (pH->iMax > pH->iEnd)) || 
         ((pH->iMax > pH->iBgn) && (pH->iMax <= pH->iEnd)))
    {
        L2_UXM_E("err list!\n");
        return L2_NOK;
    }

    if (iItem >= pH->iMax)
    {
        L2_UXM_E("err index!\n");
        return L2_NOK;
    }
    
    if ((pH->iMax) < 0xFF)
    {
        L2UdalItem1 *pI =(L2UdalItem1 *) (pH->pBas + pH->iSize * iItem);
        if ((pH->iMax) <= pH->iEnd)     /* null list */
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFF;
        }
        else        /* no-empty list */
        {
            L2BdalItem1 *pT = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFF;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        L2UdalItem2 *pI =(L2UdalItem2 *) (pH->pBas + pH->iSize * iItem);
        if (0xFFFF <= pH->iEnd)
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFFFF;
        }
        else
        {
            L2BdalItem2 *pT = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFFFF;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        L2UdalItem4 *pI =(L2UdalItem4 *) (pH->pBas + pH->iSize * iItem);
        if (0xFFFFFFFF <= pH->iEnd)
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFFFFFFFF;
        }
        else
        {
            L2UdalItem4 *pT = (L2UdalItem4 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFFFFFFFF;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }

    return L2_NOK;
}

UINT32 L2UdalPull(void *pHandle)
{

    if(NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }

    L2ArrayList *pH = (L2ArrayList *) pHandle;
    if ((pH->iMax <= pH->iBgn) && (pH->iMax <= pH->iEnd))
    {
        L2_UXM_H("empty list!\n");
        return 0xFFFFFFFF;
    }
    else if ((pH->iMax <= pH->iBgn) || (pH->iMax <= pH->iEnd))
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }

    if ((pH->iMax) < 0xFF)
    {
        UINT32 iPos = pH->iBgn;
        L2UdalItem1 *pI = (L2UdalItem1 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFF;
            pH->iEnd = 0xFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
        }
        pI->iNxt=0xFF;

        return iPos;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        UINT32 iPos = pH->iBgn;
        L2UdalItem2 *pI = (L2UdalItem2 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFFFF;
            pH->iEnd = 0xFFFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                L2MemPoolDump(1);
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
        }
        pI->iNxt=0xFFFF;
        return iPos;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        UINT32 iPos = pH->iBgn;
        L2UdalItem4 *pI = (L2UdalItem4 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFFFFFFFF;
            pH->iEnd = 0xFFFFFFFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
        }
        pI->iNxt=0xFFFFFFFF;
        return iPos;
    }

    return 0xFFFFFFFF;
}

UINT32 L2UdalIter(void *pHandle, UINT32 iPos)
{

    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }
    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ((pH->iMax) < 0xFF)
    {
        if ((0xFF==pH->iBgn)||(0xFF==pH->iEnd))
        {
            L2_UXM_E("empty list!\n");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2UdalItem1 *pI = (L2UdalItem1 *) (pH->pBas + pH->iSize * iPos);
            if (0xFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2UdalItem1 *pI = (L2UdalItem1 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        if ((0xFFFF==pH->iBgn)||(0xFFFF==pH->iEnd))
        {
            L2_UXM_E("empty list!");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2UdalItem2 *pI = (L2UdalItem2 *) (pH->pBas + pH->iSize * iPos);
            if (0xFFFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2UdalItem2 *pI = (L2UdalItem2 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        if ((0xFFFFFFFF==pH->iBgn)||(0xFFFFFFFF==pH->iEnd))
        {
            L2_UXM_E("empty list!\n");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2UdalItem4 *pI = (L2UdalItem4 *) (pH->pBas + pH->iSize * iPos);
            if (0xFFFFFFFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2UdalItem4 *pI = (L2UdalItem4 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    L2_UXM_E("err list!\n");
    return 0xFFFFFFFF;


}

/* line bi-direct list */
INT32 L2BdlPush(void *pHandle, void *pItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return L2_NOK;
    }
    if (NULL == pItem)
    {
        L2_UXM_E("err item!\n");
        return L2_NOK;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    L2BdlItem *pI = (L2BdlItem *)pItem;
    if (NULL == pH->pEnd)
    {
        pH->pBgn = pItem;
        pH->pEnd = pItem;
        pI->pNxt = NULL;
        pI->pPrv = NULL;
    }
    else
    {
        pI->pNxt = NULL;
        pI->pPrv = pH->pEnd;
        ((L2BdlItem *) (pH->pEnd))->pNxt = pItem;
        pH->pEnd = pItem;
    }
    return L2_OK;
}

void *L2BdlPull(void *pHandle)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return NULL;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    if (NULL == pH->pBgn)
    {
        return NULL;
    }
    L2BdlItem *pI = (L2BdlItem *) (pH->pBgn);
    if((pH->pBgn) == (pH->pEnd))
    {
        pH->pBgn = NULL;
        pH->pEnd = NULL;
    }
    else
    {
        pH->pBgn = pI->pNxt;
        ((L2BdlItem *)(pH->pBgn))->pPrv = NULL;
    }
    pI->pNxt = NULL;
    pI->pPrv = NULL;
    return pI;
}

INT32 L2BdlIns(void *pHandle,void *pPos,void *pItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return L2_NOK;
    }
    if (NULL == pItem)
    {
        L2_UXM_E("err item!\n");
        return L2_NOK;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    L2BdlItem *pI = (L2BdlItem *)pItem;
    if (NULL == pPos)
    {
        if(NULL == pH->pBgn)
        {
            pH->pBgn = pItem;
            pH->pEnd = pItem;
            pI->pNxt = NULL;
            pI->pPrv = NULL;
        }
        else
        {
            pI->pPrv = NULL;
            pI->pNxt = pH->pBgn;
            ((L2BdlItem *) (pH->pBgn))->pPrv = pI;
            pH->pBgn = pItem;
        }
        return L2_OK;
    }
    else if (pH->pEnd == pPos)
    {
        return L2BdlPush(pHandle, pItem);
    }
    else
    {
        L2BdlItem *pP = (L2BdlItem *)pPos;
        pI->pPrv = pP;
        pI->pNxt = pP->pNxt;
        ((L2BdlItem *) (pP->pNxt))->pPrv = pI;
        pP->pNxt = pI;
        return L2_OK;
    }
}


INT32 L2BdlDel(void *pHandle,void *pItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return L2_NOK;
    }
    if (NULL == pItem)
    {
        L2_UXM_E("err item!\n");
        return L2_NOK;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    L2BdlItem *pI = (L2BdlItem *)pItem;
    if((pH->pBgn == pI)&&(pH->pEnd == pI))
    {
        pH->pBgn = NULL;
        pH->pEnd = NULL;
        return L2_OK;
    }
    if (pH->pBgn == pI)
    {
        pH->pBgn = pI->pNxt;
        ((L2BdlItem *) (pI->pNxt))->pPrv = NULL;
    }
    else if (pH->pEnd == pI)
    {
        pH->pEnd = pI->pPrv;
        ((L2BdlItem *) (pI->pPrv))->pNxt = NULL;
    }
    else
    {
        ((L2BdlItem *) (pI->pPrv))->pNxt = pI->pNxt;
        ((L2BdlItem *) (pI->pNxt))->pPrv = pI->pPrv;
    }
    pI->pNxt = NULL;
    pI->pPrv = NULL;
    return L2_OK;
}

void *L2BdlIter(void *pHandle,void *pPos)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return NULL;
    }
    L2PointerList *pH = (L2PointerList *)pHandle;
    if((NULL == pH->pBgn) || (NULL == pH->pEnd)){
        L2_UXM_E("empty list!\n");
        return NULL;
    }    

    L2BdlItem *pP = (L2BdlItem *)pPos;
    if (NULL == pP)
    {
        return pH->pBgn;
    }
    else if (pH->pEnd == pP)
    {
        return NULL;
    }
    else
    {
        return pP->pNxt;
    }
}

/* line bi-direct array list */
INT32 L2BdalPush(void *pHandle, UINT32 iItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return L2_NOK;
    }

    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ( ((pH->iMax <= pH->iBgn) && (pH->iMax > pH->iEnd)) || 
         ((pH->iMax > pH->iBgn) && (pH->iMax <= pH->iEnd)))
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }

    if (iItem >= pH->iMax)
    {
        L2_UXM_E("err index!\n");
        return L2_NOK;
    }
    
    if ((pH->iMax) < 0xFF)
    {
        L2BdalItem1 *pI =(L2BdalItem1 *) (pH->pBas + pH->iSize * iItem);
        if (pH->iMax <= pH->iEnd)     /* null list */
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFF;
            pI->iPrv = 0xFF;
        }
        else        /* no-empty list */
        {
            L2BdalItem1 *pT = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFF;
            pI->iPrv = pH->iEnd;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        L2BdalItem2 *pI =(L2BdalItem2 *) (pH->pBas + pH->iSize * iItem);
        if (0xFFFF <= pH->iEnd)
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFFFF;
            pI->iPrv = 0xFFFF;
        }
        else
        {
            L2BdalItem2 *pT = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFFFF;
            pI->iPrv = pH->iEnd;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        L2BdalItem4 *pI =(L2BdalItem4 *) (pH->pBas + pH->iSize * iItem);
        if (0xFFFFFFFF <= pH->iEnd)
        {
            pH->iEnd = iItem;
            pH->iBgn = iItem;
            pI->iNxt = 0xFFFFFFFF;
            pI->iPrv = 0xFFFFFFFF;
        }
        else
        {
            L2BdalItem4 *pT = (L2BdalItem4 *) (pH->pBas + pH->iSize * pH->iEnd);
            pI->iNxt = 0xFFFFFFFF;
            pI->iPrv = pH->iEnd;
            pT->iNxt = iItem;
            pH->iEnd = iItem;
        }
        return L2_OK;
    }
    return L2_NOK;
}

UINT32 L2BdalPull(void *pHandle)
{

    if(NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }

    L2ArrayList *pH = (L2ArrayList *) pHandle;
    if ((pH->iMax <= pH->iBgn) && (pH->iMax <= pH->iEnd))
    {
        L2_UXM_H("empty list!\n");
        return 0xFFFFFFFF;
    }
    else if ((pH->iMax <= pH->iBgn) || (pH->iMax <= pH->iEnd))
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }

    if ((pH->iMax) < 0xFF)
    {
        UINT32 iPos = pH->iBgn;
        L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFF;
            pH->iEnd = 0xFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
            L2BdalItem1 *pT = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv= 0xFF;
        }
        pI->iNxt=0xFF;
        pI->iPrv=0xFF;
        return iPos;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        UINT32 iPos = pH->iBgn;
        L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFFFF;
            pH->iEnd = 0xFFFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
            L2BdalItem2 *pT = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv= 0xFFFF;
        }
        pI->iNxt=0xFFFF;
        pI->iPrv=0xFFFF;
        return iPos;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        UINT32 iPos = pH->iBgn;
        L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iPos);
        if((pH->iBgn) == (pH->iEnd))
        {
            pH->iBgn = 0xFFFFFFFF;
            pH->iEnd = 0xFFFFFFFF;
        }
        else
        {
            if (pH->iMax <= pI->iNxt)
            {
                L2_UXM_E("err list!\n");
                return 0xFFFFFFFF;
            }
            pH->iBgn = pI->iNxt;
            L2BdalItem4 *pT = (L2BdalItem4 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv= 0xFFFFFFFF;
        }
        pI->iNxt=0xFFFFFFFF;
        pI->iPrv=0xFFFFFFFF;
        return iPos;
    }
    return 0xFFFFFFFF;
}

INT32 L2BdalIns(void *pHandle,UINT32 iPos,UINT32 iItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("empty list!\n");
        return L2_NOK;
    }
    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ((pH->iMax) < 0xFF)
    {
        if (0xFF == iPos)
        {
            L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iItem);
            if ((0xFF == pH->iBgn) || (0xFF == pH->iEnd))
            {
                pH->iBgn = iItem;
                pH->iEnd = iItem;
                pI->iNxt = 0xFF;
                pI->iPrv = 0xFF;
            }
            else
            {
                L2BdalItem1 *pP = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iBgn);
                pP->iPrv = iItem;
                pI->iPrv = 0xFF;
                pI->iNxt = pH->iBgn;
                pH->iBgn = iItem;
            }
            return L2_OK;
        }
        else if (pH->iEnd == iPos)
        {
            return L2BdalPush(pHandle, iItem);
        }
        else if (iPos < pH->iMax)
        {
            L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iItem);
            L2BdalItem1 *pP = (L2BdalItem1 *) (pH->pBas + pH->iSize * iPos);
            L2BdalItem1 *pN = (L2BdalItem1 *) (pH->pBas + pH->iSize * pP->iNxt);
            pI->iPrv = iPos;
            pI->iNxt = pP->iNxt;
            pN->iPrv = iItem;
            pP->iNxt = iItem;
            return L2_OK;
        }
        return L2_NOK;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        if (0xFFFF == iPos)
        {
            L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iItem);
            if ((0xFFFF == pH->iBgn) || (0xFFFF == pH->iEnd))
            {
                pH->iBgn = iItem;
                pH->iEnd = iItem;
                pI->iNxt = 0xFFFF;
                pI->iPrv = 0xFFFF;
            }
            else
            {
                L2BdalItem2 *pP = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iBgn);
                pP->iPrv = iItem;
                pI->iPrv = 0xFFFF;
                pI->iNxt = pH->iBgn;
                pH->iBgn = iItem;
            }
            return L2_OK;
        }
        else if (pH->iEnd == iPos)
        {
            return L2BdalPush(pHandle, iItem);
        }
        else if (iPos < pH->iMax)
        {
            L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iItem);
            L2BdalItem2 *pP = (L2BdalItem2 *) (pH->pBas + pH->iSize * iPos);
            L2BdalItem2 *pN = (L2BdalItem2 *) (pH->pBas + pH->iSize * pP->iNxt);
            pI->iPrv = iPos;
            pI->iNxt = pP->iNxt;
            pN->iPrv = iItem;
            pP->iNxt = iItem;
            return L2_OK;
        }
        return L2_NOK;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        if (0xFFFFFFFF == iPos)
        {
            L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iItem);
            if ((0xFFFFFFFF == pH->iBgn) || (0xFFFFFFFF == pH->iEnd))
            {
                pH->iBgn = iItem;
                pH->iEnd = iItem;
                pI->iNxt = 0xFFFFFFFF;
                pI->iPrv = 0xFFFFFFFF;
            }
            else
            {
                L2BdalItem4 *pP = (L2BdalItem4 *) (pH->pBas + pH->iSize * pH->iBgn);
                pP->iPrv = iItem;
                pI->iPrv = 0xFFFFFFFF;
                pI->iNxt = pH->iBgn;
                pH->iBgn = iItem;
            }
            return L2_OK;
        }
        else if (pH->iEnd == iPos)
        {
            return L2BdalPush(pHandle, iItem);
        }
        else if (iPos < pH->iMax)
        {
            L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iItem);
            L2BdalItem4 *pP = (L2BdalItem4 *) (pH->pBas + pH->iSize * iPos);
            L2BdalItem4 *pN = (L2BdalItem4 *) (pH->pBas + pH->iSize * pP->iNxt);
            pI->iPrv = iPos;
            pI->iNxt = pP->iNxt;
            pN->iPrv = iItem;
            pP->iNxt = iItem;
            return L2_OK;
        }
        return L2_NOK;
    }
    return L2_NOK;
}

INT32 L2BdalDel(void *pHandle, UINT32 iItem)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return L2_NOK;
    }
    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ((pH->iMax) < 0xFF)
    {
        if (pH->iMax <= iItem)
        {
            L2_UXM_E("err index!\n");
            return L2_NOK;
        }
        L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iItem);
        if (pH->iBgn == pH->iEnd)
        {
            if ((pH->iBgn != iItem) || (pH->iEnd != iItem))
            {
                L2_UXM_E("err link!\n");
            }
            pH->iBgn = 0xFF;
            pH->iEnd = 0xFF;
        }
        else if (pH->iEnd == iItem)
        {
            pH->iEnd=pI->iPrv;
            L2BdalItem1 *pT = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iEnd);
            pT->iNxt = 0xFF;
        }
        else if (pH->iBgn == iItem)
        {
            pH->iBgn=pI->iNxt;
            L2BdalItem1 *pT = (L2BdalItem1 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv = 0xFF;
        }
        else
        {
            L2BdalItem1 *pL = (L2BdalItem1 *) (pH->pBas + pH->iSize * pI->iPrv);
            L2BdalItem1 *pR = (L2BdalItem1 *) (pH->pBas + pH->iSize * pI->iNxt);
            pL->iNxt = pI->iNxt;
            pR->iPrv = pI->iPrv;
        }
        pI->iNxt = 0xFF;
        pI->iPrv = 0xFF;
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        if (pH->iMax <= iItem)
        {
            L2_UXM_E("err index!\n");
            return L2_NOK;
        }
        L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iItem);
        if (pH->iBgn == pH->iEnd)
        {
            if ((pH->iBgn != iItem) || (pH->iEnd != iItem))
            {
                L2_UXM_E("err link!\n");
            }
            pH->iBgn = 0xFFFF;
            pH->iEnd = 0xFFFF;
        }
        else if (pH->iEnd == iItem)
        {
            pH->iEnd=pI->iPrv;
            L2BdalItem2 *pT = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iEnd);
            pT->iNxt = 0xFFFF;
        }
        else if (pH->iBgn == iItem)
        {
            pH->iBgn=pI->iNxt;
            L2BdalItem2 *pT = (L2BdalItem2 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv = 0xFFFF;
        }
        else
        {
            L2BdalItem2 *pL = (L2BdalItem2 *) (pH->pBas + pH->iSize * pI->iPrv);
            L2BdalItem2 *pR = (L2BdalItem2 *) (pH->pBas + pH->iSize * pI->iNxt);
            pL->iNxt = pI->iNxt;
            pR->iPrv = pI->iPrv;
        }
        pI->iNxt = 0xFFFF;
        pI->iPrv = 0xFFFF;
        return L2_OK;
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        if (pH->iMax <= iItem)
        {
            L2_UXM_E("err index!\n");
            return L2_NOK;
        }
        L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iItem);
        if (pH->iBgn == pH->iEnd)
        {
            if ((pH->iBgn != iItem) || (pH->iEnd != iItem))
            {
                L2_UXM_E("err link!\n");
            }
            pH->iBgn = 0xFFFFFFFF;
            pH->iEnd = 0xFFFFFFFF;
        }
        else if (pH->iEnd == iItem)
        {
            pH->iEnd=pI->iPrv;
            L2BdalItem4 *pT = (L2BdalItem4 *) (pH->pBas + pH->iSize * pH->iEnd);
            pT->iNxt = 0xFFFFFFFF;
        }
        else if (pH->iBgn == iItem)
        {
            pH->iBgn=pI->iNxt;
            L2BdalItem4 *pT = (L2BdalItem4 *) (pH->pBas + pH->iSize * pH->iBgn);
            pT->iPrv = 0xFFFFFFFF;
        }
        else
        {
            L2BdalItem4 *pL = (L2BdalItem4 *) (pH->pBas + pH->iSize * pI->iPrv);
            L2BdalItem4 *pR = (L2BdalItem4 *) (pH->pBas + pH->iSize * pI->iNxt);
            pL->iNxt = pI->iNxt;
            pR->iPrv = pI->iPrv;
        }
        pI->iNxt = 0xFFFFFFFF;
        pI->iPrv = 0xFFFFFFFF;
        return L2_OK;
    }
    return L2_NOK;
}

UINT32 L2BdalIter(void *pHandle, UINT32 iPos)
{
    if (NULL == pHandle)
    {
        L2_UXM_E("err list!\n");
        return 0xFFFFFFFF;
    }
    L2ArrayList *pH = (L2ArrayList *)pHandle;
    if ((pH->iMax) < 0xFF)
    {
        if ((0xFF==pH->iBgn)||(0xFF==pH->iEnd))
        {
            L2_UXM_E("empty list!\n");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iPos);
            if (0xFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2BdalItem1 *pI = (L2BdalItem1 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    else if ((pH->iMax) < 0xFFFF)
    {
        if ((0xFFFF==pH->iBgn)||(0xFFFF==pH->iEnd))
        {
            L2_UXM_E("empty list!\n");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iPos);
            if (0xFFFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2BdalItem2 *pI = (L2BdalItem2 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    else if ((pH->iMax) < 0xFFFFFFFF)
    {
        if ((0xFFFFFFFF==pH->iBgn)||(0xFFFFFFFF==pH->iEnd))
        {
            L2_UXM_E("empty list!\n");
            return 0xFFFFFFFF;
        }
        if (iPos >= pH->iMax)
        {
            return pH->iBgn;
        }
        else if (iPos == pH->iEnd)
        {
            L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iPos);
            if (0xFFFFFFFF != pI->iNxt)
            {
                L2_UXM_L("list err, link is open!\n");
            }
            return 0xFFFFFFFF;
        }
        else
        {
            L2BdalItem4 *pI = (L2BdalItem4 *) (pH->pBas + pH->iSize * iPos);
            return pI->iNxt;
        }
    }
    L2_UXM_E("err list!\n");
    return 0xFFFFFFFF;
}

