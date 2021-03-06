#include "../mac-802_11_management_framebody.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	u_char			optional_info_flag;
	bool			WithFH;
	bool			WithDS;
	bool			WithCF;
	bool			WithIBSS;
	bool			WithTIM;

	unsigned int		SSID_Len;
	unsigned int		SupportedRates_Len;
	unsigned int		PartialVirtualBitmap_Len;

	unsigned int		framebody_len;
	char			*framebody;
	
	unsigned long long 	timestamp;
	unsigned short		BeaconInterval;

	bool			ESS;
	bool			IBSS;
	bool			CFPollable;
	bool			CFPollRequest;
	bool			Privacy;

	unsigned int		SSID;

	char			*SupportedRates;

	unsigned short		DwellTime;
	u_char			HopSet;
	u_char			HopPattern;
	u_char			HopIndex;

	u_char			CurrentChannel;

	u_char			CFP_Count;
	u_char			CFP_Period;
	unsigned short		CFP_MaxDuration;
	unsigned short		CFP_DurRemaining;

	unsigned short		ATIM_Window;

	u_char			DTIM_Count;
	u_char			DTIM_Period;
	u_char			Bitmap_Control;
	char			*PartialVirtualBitmap;

	char			*CapabilityInfo;

	void			*tmp_void_ptr;
	char			*tmp_char_ptr;

	/* Build frame body */
	WithFH = true;
	WithDS = true;
	WithCF = true;
	WithIBSS = true;
	WithTIM = true;
	optional_info_flag = SpecifyWithOrWithoutSomeOptionalInfoFlagFor80211BeaconFrameBody(WithFH, WithDS, WithCF, WithIBSS, WithTIM);

	SSID_Len = 4;
	SupportedRates_Len = 8;
	PartialVirtualBitmap_Len = 10;
	framebody_len = Calculate80211BeaconFrameBodyLength(optional_info_flag, SSID_Len, SupportedRates_Len, PartialVirtualBitmap_Len);

	framebody = (char *)malloc(framebody_len);
	InitializeFrameBodyWithZero(framebody, framebody_len);

	timestamp = 10;
	SetTimestampInto80211BeaconFrameBody(framebody, &timestamp); 
	printf("\e[0;31;40mSet\e[m timestamp = %llu\n", timestamp);

	BeaconInterval = 2;
	SetBeaconIntervalInto80211BeaconFrameBody(framebody, &BeaconInterval);
	printf("\e[0;31;40mSet\e[m BeaconInterval = %d\n", BeaconInterval);

	ESS = true;
	IBSS = false;
	CFPollable = true;
	CFPollRequest = false;
	Privacy = true;
	SetCapabilityInfoInto80211BeaconFrameBody(framebody, ESS, IBSS, CFPollable, CFPollRequest, Privacy);
	if(ESS)
	   printf("\e[0;31;40mSet\e[m ESS = 1\n");
	else
	   printf("\e[0;31;40mSet\e[m ESS = 0\n");
	if(IBSS)
	   printf("\e[0;31;40mSet\e[m IBSS = 1\n");
	else
	   printf("\e[0;31;40mSet\e[m IBSS = 0\n");
	if(CFPollable)
	   printf("\e[0;31;40mSet\e[m CFPollable = 1\n");
	else
	   printf("\e[0;31;40mSet\e[m CFPollable = 0\n");
	if(CFPollRequest)
	   printf("\e[0;31;40mSet\e[m CFPollRequest = 1\n");
	else
	   printf("\e[0;31;40mSet\e[m CFPollRequest = 0\n");
	if(Privacy)
	   printf("\e[0;31;40mSet\e[m Privacy = 1\n");
	else
	   printf("\e[0;31;40mSet\e[m Privacy = 0\n");


	SSID = 12;
	SetSSIDInto80211BeaconFrameBody(framebody, SSID_Len, &SSID);
	printf("\e[0;31;40mSet\e[m SSID = %d\n", SSID);

	SupportedRates = (char *)malloc(SupportedRates_Len);
	strncpy(SupportedRates, "12345678", SupportedRates_Len);
	SetSupportedRatesInto80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len, (void *)SupportedRates);
	printf("\e[0;31;40mSet\e[m SupportedRates_Len = %d\n", SupportedRates_Len);
	if(SupportedRates != NULL && SupportedRates_Len != 0) 
		printf("\e[0;31;40mSet\e[m SupportedRates -> %s\n", SupportedRates);
	free((void *)SupportedRates);

	DwellTime = 13;
	HopSet = 0x11;
	HopPattern = 0x22;
	HopIndex = 0x33;
	SetFHParameterSetInto80211BeaconFrameBody(framebody, optional_info_flag, SSID_Len, SupportedRates_Len, &DwellTime, HopSet, HopPattern, HopIndex);
	if(WithFH) {
		printf("\e[0;31;40mSet\e[m DwellTime = %d\n", DwellTime);
		printf("\e[0;31;40mSet\e[m HopSet = %x\n", HopSet);
		printf("\e[0;31;40mSet\e[m HopPattern = %x\n", HopPattern);
		printf("\e[0;31;40mSet\e[m HopIndex = %x\n", HopIndex);
	}


	CurrentChannel = 0x44;
	SetDSParameterSetInto80211BeaconFrameBody(framebody, optional_info_flag, SSID_Len, SupportedRates_Len, CurrentChannel);
	if(WithDS) {
		printf("\e[0;31;40mSet\e[m CurrentChannel = %x\n", CurrentChannel);
	}

	CFP_Count = 0x55;
	CFP_Period = 0x66;
	CFP_MaxDuration = 14;
	CFP_DurRemaining = 15;
	SetCFParameterSetInto80211BeaconFrameBody(framebody, optional_info_flag, SSID_Len, SupportedRates_Len, CFP_Count, CFP_Period, &CFP_MaxDuration, &CFP_DurRemaining);
	if(WithCF) {
		printf("\e[0;31;40mSet\e[m CFP_Count = %x\n", CFP_Count);
		printf("\e[0;31;40mSet\e[m CFP_Period = %x\n", CFP_Period);
		printf("\e[0;31;40mSet\e[m CFP_MaxDuration = %d\n", CFP_MaxDuration);
		printf("\e[0;31;40mSet\e[m CFP_DurRemaining = %d\n", CFP_DurRemaining);
	}
	
	ATIM_Window = 16;
	SetIBSSParameterSetInto80211BeaconFrameBody(framebody, optional_info_flag, SSID_Len, SupportedRates_Len, &ATIM_Window);	
	if(WithIBSS) {
		printf("\e[0;31;40mSet\e[m ATIM_Window = %d\n",ATIM_Window);
	}


	DTIM_Count = 0x77;
	DTIM_Period = 0x88;
	Bitmap_Control = 0x99;	
	PartialVirtualBitmap = (char *)malloc(PartialVirtualBitmap_Len);
	strncpy(PartialVirtualBitmap, "ABCDEFGHIJ", PartialVirtualBitmap_Len);
	SetTIMInto80211BeaconFrameBody(framebody, optional_info_flag, SSID_Len, SupportedRates_Len, DTIM_Count, DTIM_Period, Bitmap_Control, PartialVirtualBitmap_Len, (void *)PartialVirtualBitmap);
	if(WithTIM) {
		printf("\e[0;31;40mSet\e[m DTIM_Count = %x\n", DTIM_Count);
		printf("\e[0;31;40mSet\e[m DTIM_Period = %x\n", DTIM_Period);
		printf("\e[0;31;40mSet\e[m Bitmap_Control = %x\n", Bitmap_Control);
		printf("\e[0;31;40mSet\e[m PartialVirtualBitmap_Len = %d\n", PartialVirtualBitmap_Len);
		if(PartialVirtualBitmap != NULL && PartialVirtualBitmap_Len != 0) 
			printf("\e[0;31;40mSet\e[m PartialVirtualBitmap -> %s\n", PartialVirtualBitmap);
	}
	free((void *)PartialVirtualBitmap);


	/*==Get=========================*/
	GetTimestampFrom80211BeaconFrameBody(framebody, &timestamp);
	printf("\e[0;32;40mGet\e[m timestamp = %llu\n", timestamp);

	GetBeaconIntervalFrom80211BeaconFrameBody(framebody, &BeaconInterval);
	printf("\e[0;32;40mGet\e[m BeaconInterval = %d\n", BeaconInterval);

	CapabilityInfo = GetCapabilityInfoFrom80211BeaconFrameBody(framebody);
	if(GetESSFrom80211CapabilityInfo(CapabilityInfo) == true)
	   printf("\e[0;32;40mGet\e[m ESS = 1\n");
	else
	   printf("\e[0;32;40mGet\e[m ESS = 0\n");
	if(GetIBSSFrom80211CapabilityInfo(CapabilityInfo) == true)
	   printf("\e[0;32;40mGet\e[m IBSS = 1\n");
	else
	   printf("\e[0;32;40mGet\e[m IBSS = 0\n");
	if(GetCFPollableFrom80211CapabilityInfo(CapabilityInfo) == true)
	   printf("\e[0;32;40mGet\e[m CFPollable = 1\n");
	else
	   printf("\e[0;32;40mGet\e[m CFPollable = 0\n");
	if(GetCFPollRequestFrom80211CapabilityInfo(CapabilityInfo) == true)
	   printf("\e[0;32;40mGet\e[m CFPollRequest = 1\n");
	else
	   printf("\e[0;32;40mGet\e[m CFPollRequest = 0\n");
	if(GetPrivacyFrom80211CapabilityInfo(CapabilityInfo) == true)
	   printf("\e[0;32;40mGet\e[m Privacy = 1\n");
	else
	   printf("\e[0;32;40mGet\e[m Privacy = 0\n");

	SSID_Len = 0;
	tmp_void_ptr = GetSSIDFrom80211BeaconFrameBody(framebody, &SSID_Len);
	if(tmp_void_ptr != NULL && SSID_Len != 0) {
		bcopy(tmp_void_ptr, (void *)&SSID, SSID_Len);
		printf("\e[0;32;40mGet\e[m SSID = %d\n", SSID);
	}

	tmp_void_ptr = GetSupportedRatesFrom80211BeaconFrameBody(framebody, SSID_Len, &SupportedRates_Len);
	if(tmp_void_ptr != NULL && SupportedRates_Len != 0) {
		SupportedRates = (char *)malloc(SupportedRates_Len);
		strncpy(SupportedRates, (char *)tmp_void_ptr, SupportedRates_Len);
		SupportedRates[SupportedRates_Len] = '\0';
		printf("\e[0;32;40mGet\e[m SupportedRates_Len = %d\n", SupportedRates_Len);
		printf("\e[0;32;40mGet\e[m SupportedRates -> %s\n", SupportedRates);
		free((void *)SupportedRates);
	}

	tmp_char_ptr = GetFHParameterSetFrom80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len);
	if(tmp_char_ptr != NULL) {
		if(GetDwellTimeFrom80211FHParameterSet(tmp_char_ptr, &DwellTime) == true)
			printf("\e[0;32;40mGet\e[m DwellTime = %d\n", DwellTime);
		if(GetHopSetFrom80211FHParameterSet(tmp_char_ptr, &HopSet) == true)
			printf("\e[0;32;40mGet\e[m HopSet = %x\n", HopSet);
		if(GetHopPatternFrom80211FHParameterSet(tmp_char_ptr, &HopPattern) == true)
			printf("\e[0;32;40mGet\e[m HopPattern = %x\n", HopPattern);
		if(GetHopIndexFrom80211FHParameterSet(tmp_char_ptr, &HopIndex) == true)
			printf("\e[0;32;40mGet\e[m HopIndex = %x\n", HopIndex);

	}

	tmp_char_ptr = GetDSParameterSetFrom80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len);
	if(tmp_char_ptr != NULL) {
		if(GetCurrentChannelFrom80211DSParameterSet(tmp_char_ptr, &CurrentChannel) == true)
			printf("\e[0;32;40mGet\e[m CurrentChannel = %x\n", CurrentChannel);
	}

	tmp_char_ptr = GetCFParameterSetFrom80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len);
	if(tmp_char_ptr != NULL) {
		if(GetCountFrom80211CFParameterSet(tmp_char_ptr, &CFP_Count) == true)
			printf("\e[0;32;40mGet\e[m CFP_Count = %x\n", CFP_Count);
		if(GetPeriodFrom80211CFParameterSet(tmp_char_ptr, &CFP_Period) == true)
			printf("\e[0;32;40mGet\e[m CFP_Period = %x\n", CFP_Period);
		if(GetMaxDurationFrom80211CFParameterSet(tmp_char_ptr, &CFP_MaxDuration) == true)
			printf("\e[0;32;40mGet\e[m CFP_MaxDuration = %d\n", CFP_MaxDuration);
		if(GetDurRemainingFrom80211CFParameterSet(tmp_char_ptr, &CFP_DurRemaining) == true)
			printf("\e[0;32;40mGet\e[m CFP_DurRemaining = %d\n", CFP_DurRemaining);
	}

	tmp_char_ptr = GetIBSSParameterSetFrom80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len);
	if(tmp_char_ptr != NULL) { 
		if(GetATIMWindowFrom80211IBSSParameterSet(tmp_char_ptr, &ATIM_Window) == true)  
			printf("\e[0;32;40mGet\e[m ATIM_Window = %d\n",ATIM_Window);
	}

	tmp_char_ptr = GetTIMFrom80211BeaconFrameBody(framebody, SSID_Len, SupportedRates_Len);
	if(tmp_char_ptr != NULL) {
		if(GetCountFrom80211TIM(tmp_char_ptr, &DTIM_Count) == true)
			printf("\e[0;32;40mGet\e[m DTIM_Count = %x\n", DTIM_Count);
		if(GetPeriodFrom80211TIM(tmp_char_ptr, &DTIM_Period) == true)
			printf("\e[0;32;40mGet\e[m DTIM_Period = %x\n", DTIM_Period);
		if(GetBitmapCtrlFrom80211TIM(tmp_char_ptr, &Bitmap_Control) == true)
			printf("\e[0;32;40mGet\e[m Bitmap_Control = %x\n", Bitmap_Control);
		PartialVirtualBitmap_Len = 0;
		tmp_void_ptr = (char *)GetPartialVirtualBitmapFrom80211TIM(tmp_char_ptr, &PartialVirtualBitmap_Len);
		if(tmp_void_ptr != NULL && PartialVirtualBitmap_Len != 0) {
			PartialVirtualBitmap = (char *)malloc(PartialVirtualBitmap_Len);	
			strncpy(PartialVirtualBitmap, (char *)tmp_void_ptr, PartialVirtualBitmap_Len);
			PartialVirtualBitmap[PartialVirtualBitmap_Len] = '\0';
			printf("\e[0;32;40mGet\e[m PartialVirtualBitmap_Len = %d\n", PartialVirtualBitmap_Len);
			printf("\e[0;32;40mGet\e[m PartialVirtualBitmap -> %s\n", PartialVirtualBitmap);
			free((void *)PartialVirtualBitmap);
		}
	}

	free(framebody);	
	return 0;
}

