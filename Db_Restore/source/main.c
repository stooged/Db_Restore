#include "ps4.h"
#include "patch.h"

void shutdown()
{
	int evf = syscall(540, "SceSysCoreReboot");
	syscall(546, evf, 0x4000, 0);
	syscall(541, evf);
	syscall(37, 1, 30);
}

int _main(struct thread *td) {
	initKernel();
	initLibc();
	syscall(11,patcher,td);
	initSysUtil();
	int usbdir = open("/mnt/usb0/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (usbdir == -1)
	{
		usbdir = open("/mnt/usb1/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (usbdir == -1)
		{
			systemMessage("Restoring from: INTERNAL");
			if (file_exists("/system_data/priv/mms/app.db_backup"))
			{
				copy_File("/system_data/priv/mms/app.db_backup", "/system_data/priv/mms/app.db");
			}		
			if (file_exists("/system_data/priv/mms/addcont.db_backup"))
			{
				copy_File("/system_data/priv/mms/addcont.db_backup", "/system_data/priv/mms/addcont.db");
			}	
			if (file_exists("/system_data/priv/mms/av_content_bg.db_backup"))
			{
				copy_File("/system_data/priv/mms/av_content_bg.db_backup", "/system_data/priv/mms/av_content_bg.db");
			}
			systemMessage("DB Restore Complete.");
			shutdown();
			return 0;
		}
		else
		{	
			close(usbdir);
			systemMessage("Restoring from: USB1");
			unlink("/mnt/usb1/.dirtest");
			mkdir("/mnt/usb1/DB_Dackup/", 0777);	
			if (file_exists("/mnt/usb1/DB_Dackup/app.db"))
			{
				copy_File("/mnt/usb1/DB_Dackup/app.db", "/system_data/priv/mms/app.db");
			}		
			if (file_exists("/mnt/usb1/DB_Dackup/addcont.db"))
			{
				copy_File("/mnt/usb1/DB_Dackup/addcont.db", "/system_data/priv/mms/addcont.db");				
			}
			if (file_exists("/mnt/usb1/DB_Dackup/av_content_bg.db"))
			{
				copy_File("/mnt/usb1/DB_Dackup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");				
			}
		}
	}
	else
	{
		close(usbdir);
		systemMessage("Restoring from: USB0");
		unlink("/mnt/usb0/.dirtest");
		mkdir("/mnt/usb0/DB_Dackup/", 0777);			
		if (file_exists("/mnt/usb0/DB_Dackup/app.db"))
		{
			copy_File("/mnt/usb0/DB_Dackup/app.db", "/system_data/priv/mms/app.db");				
		}				
		if (file_exists("/mnt/usb0/DB_Dackup/addcont.db"))
		{
			copy_File("/mnt/usb0/DB_Dackup/addcont.db", "/system_data/priv/mms/addcont.db");				
		}
		if (file_exists("/mnt/usb0/DB_Dackup/av_content_bg.db"))
		{
			copy_File("/mnt/usb0/DB_Dackup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");				
		}
	}
	systemMessage("DB Restore Complete.");
	shutdown();
    return 0;
}
