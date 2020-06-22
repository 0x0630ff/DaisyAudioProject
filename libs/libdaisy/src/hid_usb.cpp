#include "hid_usb.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

using namespace daisy;

static void UsbErrorHandler();

// Externs for IRQ Handlers
extern "C"
{
    // Globals from Cube generated version:
    USBD_HandleTypeDef       hUsbDeviceHS;
    USBD_HandleTypeDef       hUsbDeviceFS;
    extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
    extern PCD_HandleTypeDef hpcd_USB_OTG_HS;

    void DummyRxCallback(uint8_t* buf, uint32_t *size)
    {
        // Do Nothing
    }

    CDC_ReceiveCallback rxcallback;
}

UsbHandle::ReceiveCallback rx_callback;

static void InitFS()
{
    rx_callback = DummyRxCallback;
    if(USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS)
       != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        UsbErrorHandler();
    }
}

static void InitHS()
{
    // HS as FS
    if(USBD_Init(&hUsbDeviceHS, &HS_Desc, DEVICE_HS) != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_RegisterClass(&hUsbDeviceHS, &USBD_CDC) != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_CDC_RegisterInterface(&hUsbDeviceHS, &USBD_Interface_fops_HS)
       != USBD_OK)
    {
        UsbErrorHandler();
    }
    if(USBD_Start(&hUsbDeviceHS) != USBD_OK)
    {
        UsbErrorHandler();
    }
}


void UsbHandle::Init(UsbPeriph dev)
{
    switch(dev)
    {
        case FS_INTERNAL: InitFS(); break;
        case FS_EXTERNAL: InitHS(); break;
        case FS_BOTH:
            InitHS();
            InitFS();
            break;
        default: break;
    }
    // Enable USB Regulator
    HAL_PWREx_EnableUSBVoltageDetector();
}

void UsbHandle::TransmitInternal(uint8_t* buff, size_t size)
{
    CDC_Transmit_FS(buff, size);
}
void UsbHandle::TransmitExternal(uint8_t* buff, size_t size)
{
    CDC_Transmit_HS(buff, size);
}

void UsbHandle::SetReceiveCallback(ReceiveCallback cb) 
{
	// This is pretty silly, but we're working iteritavely...
    rx_callback = cb;
    rxcallback  = (CDC_ReceiveCallback)rx_callback;
    CDC_Set_Rx_Callback_FS(rxcallback);
}

// Static Function Implementation
static void UsbErrorHandler()
{
    while(1) {}
}

// IRQ Handler
extern "C"
{
    void OTG_HS_EP1_OUT_IRQHandler(void)
    {
        HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
    }

    void OTG_HS_EP1_IN_IRQHandler(void)
    {
        HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
    }

    void OTG_HS_IRQHandler(void) { HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS); }

    void OTG_FS_EP1_OUT_IRQHandler(void)
    {
        HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
    }

    void OTG_FS_EP1_IN_IRQHandler(void)
    {
        HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
    }

    void OTG_FS_IRQHandler(void) { HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS); }
}
