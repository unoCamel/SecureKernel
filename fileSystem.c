#include "system.h"
//#include "stdio.h"
#define numberFiles 12


int totalFiles = numberFiles;
int currentDirectory=0;

int cur_file=0;



/*file system */
File FileSystem[max_file_system_size][max_file_size];
File FileIndex[max_file_system_size];

char new_path[100];
char new_pwd[100];


void FILESYSTEM_init(void){

	populate_file_system();


}

void create_file_system_array(){
	File empty={"","","","",0,0,NULL,0,0,0};
	int i=0, j=0;
	for( i=0; i<max_file_system_size; i++){
		for(j=0; j<max_file_size; j++){
			FileSystem[i][j] = empty;
		}
	}
}



void create_directory(char* name){
	int i=0;
	
	if(!strcmp(name,"")) {// Cannot make a directory with no name
			message("You need to enter directory name");
			newlineX1();
			return;
		}
	for( i=0; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, name)){//Cannot make a directory that with same path
			message("That file already exists");
			newlineX1();
			newlineX1();
			return;
		}else if(curDirectory[i].folder !=2 && curDirectory[i].folder !=1){
			//message("make new direcoty");
			strcpy(curDirectory[i].name, name);
			strcpy(curDirectory[i].desc, "");
			update_pwd(name, FileIndex[currentDirectory].basic_path);
			curDirectory[i].parent_index = currentDirectory;			
			curDirectory[i].children=(struct File*)FileSystem[totalFiles];
			curDirectory[i].privilege=3;
			curDirectory[i].index=totalFiles;
			curDirectory[i].folder=1;


			strcpy(curDirectory[i].pwd, new_pwd);
			strcpy(curDirectory[i].basic_path, new_path);
			strcpy(curDirectory[i].permissions, "drwxrwxrwx");
			strcpy(curDirectory[i].links, "2");
			strcpy(curDirectory[i].owner, "camel");
			strcpy(curDirectory[i].group, "camel");
			strcpy(curDirectory[i].size, "0");
			strcpy(curDirectory[i].date, "Mar 16  2017");
			FileIndex[totalFiles]= curDirectory[i];
			FileIndex[currentDirectory].num_files++;
			
			totalFiles++; 
			return;
		}
	}
	message("The size of this file has exceed its maximum capcity. You directory cannot be created");
	newlineX1(); 
}


void create_file(char* name, char * desc){
	int i=0;
	if(!strcmp(name,"")) { //Cannot make a file with no name
			message("You need to enter directory name");
			newlineX1();
			return;
		}
	for( ; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, name)){//Cannot make a file whos path already exists
			message("That file already exists");
			return;
		}else if(curDirectory[i].folder !=2 && curDirectory[i].folder !=1){
			strcpy(curDirectory[i].name, name);
			strcpy(curDirectory[i].desc, desc);
			update_pwd(name, FileIndex[currentDirectory].basic_path);
			curDirectory[i].parent_index = currentDirectory;
			curDirectory[i].children=(struct File*)FileSystem[totalFiles];
			curDirectory[i].privilege=3;
			curDirectory[i].index=totalFiles;
			curDirectory[i].folder=2;

			strcpy(curDirectory[i].pwd, new_pwd);
			strcpy(curDirectory[i].basic_path, new_path);
			strcpy(curDirectory[i].permissions, "drwxrwxrwx");
			strcpy(curDirectory[i].links, "2");
			strcpy(curDirectory[i].owner, "camel");
			strcpy(curDirectory[i].group, "camel");
			strcpy(curDirectory[i].size, "0");
			strcpy(curDirectory[i].date, "Mar 16  2017");
			
			FileIndex[totalFiles]= curDirectory[i];
			totalFiles++; 
			FileIndex[currentDirectory].num_files++;
			return;
		}
	}
	message("The size of this file has exceed its maximum capcity. You directory cannot be created"); 
}


void delete_file(char* name){
	int i;
	File empty={"","","","",0,0,NULL,0,0,0};
	for(i=0; i<max_file_size; i++){
		if(!strcmp(name, curDirectory[i].name)){
			if(curDirectory[i].folder==2){
				message("delete");
				strcpy(curDirectory[i].name, "");
				FileIndex[curDirectory[i].index]=empty;
				curDirectory[i]=empty;
				totalFiles--;
				newlineX1();
				strcpy(curDirectory[i].name, "");
				memset(curDirectory[i].name, '\0', 20);
				FileIndex[currentDirectory].num_files--;
			}else{
				message("Directory, not a file, cant delete using rm. Use rmdir instead.");
				newlineX1();
			}
		}
	}
}



void delete_directory(char* name){
	int i;
	File empty={"","","","",0,0,NULL,0,0,0};
	for(i=0; i<max_file_size; i++){
		if(!strcmp(name, curDirectory[i].name)){
			if(curDirectory[i].folder==1){
				FileIndex[curDirectory[i].index]=empty;
				curDirectory[i]=empty;
				totalFiles--;
				FileIndex[currentDirectory].num_files--;
			}else{
				message("File not directory, cant delete using rmdir. Use rm instead.");
				newlineX1();
			}
		}
	}
}


void update_pwd(char* name, char* parent_pwd){
	memset(new_path, '\0', 100);
	memset(new_pwd, '\0', 100);
	strcpy(new_path, strcat(strcat(parent_pwd, name), "/"));
	strcpy(new_pwd, strcat(strcat("Soteria@CAMEL:", new_path), "$ "));

}