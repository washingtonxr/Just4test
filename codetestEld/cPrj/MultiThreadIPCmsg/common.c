#include "common.h"

INT32 L2UdlPush(void *pHandle, void *pItem)
{
    if (NULL == pHandle)
    {
        printf("err list!\n");
        return L2_NOK;
    }
    if (NULL == pItem)
    {
        printf("err item!\n");
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
        printf("empty list!\n");
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

/* End of this file. */