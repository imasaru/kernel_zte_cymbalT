/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef KERNEL_VS_SERVICE_01_H
#define KERNEL_VS_SERVICE_01_H

#include <soc/qcom/msm_qmi_interface.h>

#define MEM_ALLOC_REQ_MAX_MSG_LEN_V01 255
#define MEM_FREE_REQ_MAX_MSG_LEN_V01 255
#define MAX_ARR_CNT_V01 64

struct kernel_vs_mem_alloc_addr_info_type_v01 {
	uint64_t phy_addr;
	uint32_t num_bytes;
};

enum kernel_vs_mem_proc_id_v01 {
	/* To force a 32 bit signed enum.  Do not change or use */
	KERNEL_VS_MEM_PROC_ID_MIN_ENUM_VAL_V01 = -2147483647,
	/* Request from MPSS processor */
	KERNEL_VS_MEM_PROC_MPSS_V01 = 0,
	/* Request from ADSP processor */
	KERNEL_VS_MEM_PROC_ADSP_V01 = 1,
	/* Request from WCNSS processor */
	KERNEL_VS_MEM_PROC_WCNSS_V01 = 2,
	/* To force a 32 bit signed enum.  Do not change or use */
	KERNEL_VS_MEM_PROC_ID_MAX_ENUM_VAL_V01 = 2147483647
};

enum kernel_vs_mem_client_id_v01 {
	/*To force a 32 bit signed enum.  Do not change or use*/
	KERNEL_VS_MEM_CLIENT_ID_MIN_ENUM_VAL_V01 = -2147483647,
	/*  Request from GPS Client    */
	KERNEL_VS_MEM_CLIENT_SDLOG = 0,
	/* Invalid Client */
	KERNEL_VS_MEM_CLIENT_INVALID = 1000,
	/* To force a 32 bit signed enum.  Do not change or use */
	KERNEL_VS_MEM_CLIENT_ID_MAX_ENUM_VAL_V01 = 2147483647
};

enum kernel_vs_mem_block_align_enum_v01 {
	/* To force a 32 bit signed enum.  Do not change or use
	*/
	KERNEL_VS_MEM_BLOCK_ALIGN_ENUM_MIN_ENUM_VAL_V01 = -2147483647,
	/* Align allocated memory by 2 bytes  */
	KERNEL_VS_MEM_BLOCK_ALIGN_2_V01 = 0,
	/* Align allocated memory by 4 bytes  */
	KERNEL_VS_MEM_BLOCK_ALIGN_4_V01 = 1,
	/**<  Align allocated memory by 8 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_8_V01 = 2,
	/**<  Align allocated memory by 16 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_16_V01 = 3,
	/**<  Align allocated memory by 32 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_32_V01 = 4,
	/**<  Align allocated memory by 64 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_64_V01 = 5,
	/**<  Align allocated memory by 128 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_128_V01 = 6,
	/**<  Align allocated memory by 256 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_256_V01 = 7,
	/**<  Align allocated memory by 512 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_512_V01 = 8,
	/**<  Align allocated memory by 1024 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_1K_V01 = 9,
	/**<  Align allocated memory by 2048 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_2K_V01 = 10,
	/**<  Align allocated memory by 4096 bytes */
	KERNEL_VS_MEM_BLOCK_ALIGN_4K_V01 = 11,
	KERNEL_VS_MEM_BLOCK_ALIGN_ENUM_MAX_ENUM_VAL_V01 = 2147483647
	/* To force a 32 bit signed enum.  Do not change or use
	*/
};

/* Request Message; This command is used for getting
 * the multiple physically contiguous
 * memory blocks from the server memory subsystem
 */
struct kernel_vs_mem_alloc_generic_req_msg_v01 {

	/* Mandatory */
	/*requested size*/
	uint32_t num_bytes;

	/* Mandatory */
	/* client id */
	enum kernel_vs_mem_client_id_v01 client_id;

	/* Mandatory */
	/* Peripheral Id*/
	enum kernel_vs_mem_proc_id_v01 proc_id;

	/* Mandatory */
	/* Sequence id */
	uint32_t sequence_id;

	/* Optional */
	/*  alloc_contiguous */
	/* Must be set to true if alloc_contiguous is being passed */
	uint8_t alloc_contiguous_valid;

	/* Alloc_contiguous is used to identify that clients are requesting
	 * for contiguous or non contiguous memory, default is contiguous
	* 0 = non contiguous else contiguous
	 */
	uint8_t alloc_contiguous;

	/* Optional */
	/* Must be set to true if block_alignment
	 * is being passed
	 */
	uint8_t block_alignment_valid;

	/* The block alignment for the memory block to be allocated
	*/
	enum kernel_vs_mem_block_align_enum_v01 block_alignment;

};  /* Message */

/* Response Message; This command is used for getting
 * the multiple physically contiguous memory blocks
 * from the server memory subsystem
 */
struct kernel_vs_mem_alloc_generic_resp_msg_v01 {

	/* Mandatory */
	/*  Result Code */
	/* The result of the requested memory operation
	*/
	struct qmi_response_type_v01 resp;

	/* Optional */
	/* Sequence ID */
	/* Must be set to true if sequence_id is being passed */
	uint8_t sequence_id_valid;


	/* Mandatory */
	/* Sequence id */
	uint32_t sequence_id;

	/* Optional */
	/*  Memory Block Handle
	*/
	/* Must be set to true if handle is being passed
	*/
	uint8_t kernel_vs_mem_alloc_addr_info_valid;

	/* Optional */
	/* Handle Size */
	uint32_t kernel_vs_mem_alloc_addr_info_len;

	/* Optional */
	/* The physical address of the memory allocated on the HLOS
	*/
	struct kernel_vs_mem_alloc_addr_info_type_v01
		kernel_vs_mem_alloc_addr_info[MAX_ARR_CNT_V01];

};  /* Message */

/* Request Message; This command is used for releasing
 * the multiple physically contiguous
 * memory blocks to the server memory subsystem
 */
struct kernel_vs_mem_free_generic_req_msg_v01 {

	/* Mandatory */
	/* Must be set to # of  elments in array*/
	uint32_t kernel_vs_mem_alloc_addr_info_len;

	/* Mandatory */
	/* Physical address and size of the memory allocated
	 * on the HLOS to be freed.
	 */
	struct kernel_vs_mem_alloc_addr_info_type_v01
			kernel_vs_mem_alloc_addr_info[MAX_ARR_CNT_V01];

	/* Optional */
	/* Client ID */
	/* Must be set to true if client_id is being passed */
	uint8_t client_id_valid;

	/* Optional */
	/* Client Id */
	enum kernel_vs_mem_client_id_v01 client_id;

	/* Optional */
	/* Proc ID */
	/* Must be set to true if proc_id is being passed */
	uint8_t proc_id_valid;

	/* Optional */
	/* Peripheral */
	enum kernel_vs_mem_proc_id_v01 proc_id;

};  /* Message */

/* Response Message; This command is used for releasing
 * the multiple physically contiguous
 * memory blocks to the server memory subsystem
 */
struct kernel_vs_mem_free_generic_resp_msg_v01 {

	/* Mandatory */
	/* Result of the requested memory operation, todo,
	 * need to check the async operation for free
	 */
	struct qmi_response_type_v01 resp;

};  /* Message */

extern struct elem_info kernel_vs_mem_alloc_generic_req_msg_data_v01_ei[];
extern struct elem_info kernel_vs_mem_alloc_generic_resp_msg_data_v01_ei[];
extern struct elem_info kernel_vs_mem_free_generic_req_msg_data_v01_ei[];
extern struct elem_info kernel_vs_mem_free_generic_resp_msg_data_v01_ei[];

/*Service Message Definition*/
#define KERNEL_VS_MEM_ALLOC_GENERIC_REQ_MSG_V01 0x0020
#define KERNEL_VS_MEM_ALLOC_GENERIC_RESP_MSG_V01 0x0020
#define KERNEL_VS_MEM_FREE_GENERIC_REQ_MSG_V01 0x0021
#define KERNEL_VS_MEM_FREE_GENERIC_RESP_MSG_V01 0x0021

#endif
