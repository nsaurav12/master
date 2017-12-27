/* Continuus file information --- %full_filespec: fm_test_pol_get_name.c~2:csrc:2 % */
/***********************************************************************
 *
 * @(#)fm_test_pol_get_name.c
 *
 *  Copyright (c) 2000 Portal Software, Inc. All rights reserved.
 *  This material is the confidential property of Portal Software, Inc.
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Portal license or
 *  sublicense agreement.
 *
 * Author: Sunil Narayanan
 ***********************************************************************/

#include <stdio.h>
#include <strings.h>




#include <stdlib.h>

#include "pcm.h"
#include "ops/tcf.h"
#include "cm_fm.h"
#include "pin_flds.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "pin_cust.h"
#include "custom_flds.h"
#include "fm_test_pol.h"



#define FILE_SOURCE_ID  "fm_test_pol_get_name"

/*******************************************************************
 * Routines contained herein.
 *******************************************************************/
EXPORT_OP void
op_test_pol_get_name(
    cm_nap_connection_t *connp,
    u_int               opcode,
    u_int               flags,
    pin_flist_t         *in_flistp,
    pin_flist_t         **ret_flistpp,
    pin_errbuf_t        *ebufp);

static void
fm_test_pol_get_name(
    pcm_context_t       *ctxp,
    pin_flist_t         *in_flistp,
    pin_flist_t         **out_flistpp,
    pin_errbuf_t        *ebufp);

	  
	  
	  
	  
	  
	
/*******************************************************************
 * Main routine for the PCM_OP_TEST_POL_GET_NAME opcode
 *******************************************************************/
void
op_test_pol_get_name(
    cm_nap_connection_t *connp,
    u_int               opcode,
    u_int               flags,
    pin_flist_t         *in_flistp,
    pin_flist_t         **ret_flistpp,
    pin_errbuf_t        *ebufp)
{
    pcm_context_t *ctxp = connp->dm_ctx;
    pin_flist_t *r_flistp = NULL;

    if (PIN_ERRBUF_IS_ERR(ebufp)) {
        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
            "op_test_pol_get_name: Entered with error", ebufp);
        return;
    }

    /***********************************************************
     * Null out results until we have some.
     ***********************************************************/
    *ret_flistpp = NULL;
    PIN_ERRBUF_RESET(ebufp);

    PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
        "op_test_pol_get_name: Input flist", in_flistp);

    /*****************************************************************
     * Error out in case opcode is not op_test_pol_get_name
     *****************************************************************/
    if (opcode != PCM_OP_TEST_POL_GET_NAME) {
        pin_set_err(ebufp, PIN_ERRLOC_FM,
            PIN_ERRCLASS_SYSTEM_DETERMINATE, PIN_ERR_BAD_OPCODE, 0, 0, opcode);
        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
            "op_test_pol_get_name: Bad opcode!", ebufp);
        return;
    }

    /***********************************************************
     * Call main function
     ***********************************************************/
    fm_test_pol_get_name(ctxp, in_flistp, &r_flistp, ebufp);

    /***********************************************************
     * Results.
     ***********************************************************/
    if (PIN_ERRBUF_IS_ERR(ebufp)) {
        *ret_flistpp = NULL;
        PIN_FLIST_DESTROY_EX(&r_flistp, NULL);
        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
            "op_test_pol_get_name: fm_test_pol_get_name returned error", ebufp);
    } else {
        *ret_flistpp = r_flistp;
        PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
            "op_test_pol_get_name: return flist", r_flistp);
    }

    return;
}

static void
fm_test_pol_get_name(
    pcm_context_t       *ctxp,
    pin_flist_t         *in_flistp,
    pin_flist_t         **out_flistpp,
    pin_errbuf_t        *ebufp)
{
    /* Declarations */
    int srch_flag = 0;
    int64 dbno = 0;
    poid_t *input_poidp = NULL;
    poid_t *srch_poidp = NULL;
    pin_flist_t *acc_search_in_flistp = NULL;
    pin_flist_t *acc_search_out_flistp = NULL;
    pin_flist_t *args_flistp = NULL;
    pin_flist_t *res_flistp = NULL;
    pin_flist_t *result_flistp = NULL;
    pin_flist_t *nameinfo_flistp = NULL;
    pin_flist_t *nameinfo_res_flistp = NULL;
    pin_flist_t *return_flistp = NULL;

    PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
        "fm_test_pol_get_name: Input flist", in_flistp);

    if (PIN_ERRBUF_IS_ERR(ebufp)) {
        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
            "fm_test_pol_get_name: Entered with error", ebufp);
        return;
    }

    /*Implementation */
    input_poidp = PIN_FLIST_FLD_GET(in_flistp, PIN_FLD_POID, 0, ebufp);
    dbno = PIN_POID_GET_DB(input_poidp);
    acc_search_in_flistp = PIN_FLIST_CREATE(ebufp);
    srch_poidp = PIN_POID_CREATE(dbno, "/search", -1, ebufp);
    PIN_FLIST_FLD_PUT(acc_search_in_flistp, PIN_FLD_POID, srch_poidp, ebufp);
    PIN_FLIST_FLD_SET(acc_search_in_flistp, PIN_FLD_FLAGS, &srch_flag, ebufp);
    PIN_FLIST_FLD_SET(acc_search_in_flistp,
        PIN_FLD_TEMPLATE, "select X from /account where F1 = V1 ", ebufp);
    args_flistp = PIN_FLIST_ELEM_ADD(acc_search_in_flistp, PIN_FLD_ARGS, 1, ebufp);
    PIN_FLIST_FLD_COPY(in_flistp, PIN_FLD_ACCOUNT_NO, args_flistp, PIN_FLD_ACCOUNT_NO, ebufp);
    res_flistp = PIN_FLIST_ELEM_ADD(acc_search_in_flistp, PIN_FLD_RESULTS, 0, ebufp);
    nameinfo_flistp = PIN_FLIST_ELEM_ADD(res_flistp, PIN_FLD_NAMEINFO, 1, ebufp);
    PIN_FLIST_FLD_SET(nameinfo_flistp, PIN_FLD_FIRST_NAME, NULL, ebufp);
    PIN_FLIST_FLD_SET(nameinfo_flistp, PIN_FLD_LAST_NAME, NULL, ebufp);

    PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
        "fm_test_pol_get_name: PCM_OP_SEARCH input flist", acc_search_in_flistp);
    PCM_OP(ctxp, PCM_OP_SEARCH, 0, acc_search_in_flistp, &acc_search_out_flistp, ebufp);
    PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
        "fm_test_pol_get_name: PCM_OP_SEARCH output flist", acc_search_out_flistp);

    if (PIN_ERRBUF_IS_ERR(ebufp)
        || (acc_search_out_flistp == NULL)) {
        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
            "fm_test_pol_get_name: PCM_OP_SEARCH exited with error", ebufp);
    } else {
        result_flistp = PIN_FLIST_ELEM_GET(acc_search_out_flistp, PIN_FLD_RESULTS, 0, 1, ebufp);
        if (result_flistp) {
            return_flistp = PIN_FLIST_CREATE(ebufp);
            PIN_FLIST_FLD_COPY(result_flistp, PIN_FLD_POID, return_flistp, PIN_FLD_POID, ebufp);
            nameinfo_res_flistp = PIN_FLIST_ELEM_GET(result_flistp, PIN_FLD_NAMEINFO, 1, 1, ebufp);
            if (nameinfo_res_flistp) {
                PIN_FLIST_FLD_COPY(nameinfo_res_flistp,
                    PIN_FLD_FIRST_NAME, return_flistp, PIN_FLD_FIRST_NAME, ebufp);
                PIN_FLIST_FLD_COPY(nameinfo_res_flistp,
                    PIN_FLD_LAST_NAME, return_flistp, PIN_FLD_LAST_NAME, ebufp);
            }
        }
    }

    *out_flistpp = return_flistp;
    PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
        "fm_test_pol_get_name: output flist", *out_flistpp);

    PIN_FLIST_DESTROY_EX(&acc_search_out_flistp, NULL);
    PIN_FLIST_DESTROY_EX(&acc_search_in_flistp, NULL);

    return;
}
