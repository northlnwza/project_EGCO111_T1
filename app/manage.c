#include "header.h"

typedef struct
{
	char	name[MAX_INPUT_LENGTH];
	char	detail[MAX_INPUT_LENGTH];
	char	timestamp[30];
} Device; 

void	addDevice(const char *username)
{
	FILE	*file;
	Device	newDevice;
	char	filepath[MAX_USERNAME_LENGTH + 30];

	system(CLEAR_CMD);
	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
	file = fopen(filepath, "a+");
	if (file == NULL)
	{
		printf("Error opening task");
		return;
	}
	printf("Enter a new device:");
	fgets(newDevice.name, sizeof(newDevice.name), stdin);
	newDevice.name[strcspn(newDevice.name, "\n")] = 0;
	printf("Enter device detail:");
	fgets(newDevice.detail, sizeof(newDevice.detail), stdin);
	newDevice.detail[strcspn(newDevice.detail, "\n")] = 0;
	time_t	now = time(NULL);
	struct	tm *t = localtime(&now);
	strftime(newDevice.timestamp, sizeof(newDevice.timestamp), "%Y-%m-%d-%H:%M:%S", t);
	fprintf(file, "%s, %s, %s\n", newDevice.name, newDevice.detail, newDevice.timestamp);
	fclose(file);
	printf("Device added successfully.\n");
}

void	viewDevice(const char *username)
{
	FILE	*file;
	char	filepath[MAX_USERNAME_LENGTH + 30];
	char	line[MAX_INPUT_LENGTH];
	int	deviceNumber;
	
	system(CLEAR_CMD);
	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
	file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("No device list found for %s.\n", username);
		return;
	}
	printf("Device list for %s:\n", username);
	deviceNumber = 1;
	printf("--------------------------\n");
	while (fgets(line, sizeof(line), file))
	{
		printf("%d. %s", deviceNumber++, line);
	}
	printf("--------------------------\n");
	fclose(file);
}

void	deleteDevice(const char *username)
{
	FILE	*file;
 	char	filepath[MAX_USERNAME_LENGTH + 30];
    	char	Devices[100][MAX_INPUT_LENGTH];
	int	deviceCount;
	int	deviceNumber;
	int	i;
	
	system(CLEAR_CMD);
	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
	file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("No to-do list found for %s.\n", username);
        	return;
    	}
	deviceCount = 0;
    	// Load devices into memory
	while (fgets(Devices[deviceCount], sizeof(Devices[deviceCount]), file))
	{
		deviceCount++;
	}
	fclose(file);
	if (deviceCount == 0)
	{
		printf("No devices to delete.\n");
		return;
	}
	// Display devices
	printf("Devices %s:\n", username);
	i = 0;
	while (i < deviceCount)
	{
		printf("%d. %s", i + 1, Devices[i]);
		i++;
	}
	// Ask which device to delete
	printf("Enter the number of the device to delete: ");
	scanf("%d", &deviceNumber);
	getchar();
	if (deviceNumber < 1 || deviceNumber > deviceCount)
	{
		printf("Invalid device number.\n");
		return;
	}
	// Write back all devices except the one to delete
	file = fopen(filepath, "w");
	if (file == NULL)
	{
		printf("Error opening device list for writing\n");
		return;
	}

	i = 0;
	while (i < deviceCount)
	{
		if (i != deviceNumber - 1)// Skip the task to delete
			fputs(Devices[i], file);
		i++;
	}
	fclose(file);
	printf("Device deleted successfully.\n");
}

void	editDevice(const char *username)
{
	FILE	*file;
	Device	updatedDevice;
	int	deviceCount;
	int	deviceNumber;
	int	i;
	char	filepath[MAX_USERNAME_LENGTH + 30];
	char	devices[100][MAX_INPUT_LENGTH * 3];
	char	newDevice[MAX_INPUT_LENGTH * 3];
	
	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
	file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("No device found for %s.\n", username);
		return;
	}
	deviceCount = 0;
	while (fgets(devices[deviceCount], sizeof(devices[deviceCount]), file))
	{
		deviceCount++;
	}
	fclose(file);

	if (deviceCount == 0)
	{
		printf("No devices to edit.\n");
		return;
	}
	// Display devices 
	printf("Device list for %s:\n", username);
	i = 0;
	while (i < deviceCount)
	{
		printf("%d. %s", i + 1, devices[i]);
		i++;
	}
	// Ask which device to edit
	printf("Enter the number of the device to edit: ");
	scanf("%d", &deviceNumber);
	getchar();
	if (deviceNumber < 1 || deviceNumber > deviceCount)
	{
		printf("Invalid device number\n");
		return;
	}

	//Prompt for new device description
	printf("Enter new device name:");
	fgets(updatedDevice.name, sizeof(updatedDevice.name), stdin);
	updatedDevice.name[strcspn(updatedDevice.name, "\n")] = 0;
	printf("Enter new device detail:");
	fgets(updatedDevice.detail, sizeof(updatedDevice.detail), stdin);
	updatedDevice.detail[strcspn(updatedDevice.detail, "\n")] = 0;
	strcpy(updatedDevice.timestamp, strtok(devices[deviceNumber - 1], ", "));
	strtok(NULL, ", ");
	strcpy(updatedDevice.timestamp, strtok(NULL, ", "));
	//update the device in array
	sprintf(newDevice, "%s, %s, %s", updatedDevice.name, updatedDevice.detail, updatedDevice.timestamp);
	ft_strcpy(devices[deviceNumber - 1], newDevice);
	//write updated devices back to the file 
	file = fopen(filepath, "w");
	if (file == NULL)
	{
		printf("Error opening device list for writing");
		return;
	}
	i = 0;
	while (i < deviceCount)
	{
		fputs(devices[i], file);
		i++;
	}
	fclose(file);
	printf("Device updated successfully.\n");
}	
