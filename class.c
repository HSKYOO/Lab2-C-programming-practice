#include "class.h"

char kname[2][10] = {"A+~F", "P/F"}; 


int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class* c[], int csize){
// Caution : Don't allow the duplicate class code.
// You must complete this function.

	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));

	printf(">> code number > ");
	scanf("%d", &(p->code));

	// 클래스 코드 중복 방지 -> 중복이면 csize 그대로 return
	for(int i = 0; i < csize; i++){
		if (p->code == c[i]->code){
			printf("Code duplicated! Retry\n");

			free(p);		// 할당 제거
			return csize;
		}
	}

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize+1;
}

void editClass(struct st_class* c[], int csize){
	struct st_class* p = NULL;		// 난수 차단
	int code;
	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	
	// You must complete this section.

	// 탐색
	for(int i = 0; i < csize; i++){
		if(code == c[i]->code){
			p = c[i];
			break;
		}
	}

	// 공백이면 return
	if(p == NULL){
		printf("No such class.\n");
		return;
	}

	
	printf("> Current: [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");

}


// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){	// my[] -> 내가 신청한 과목 목록
	int code = 0;
	int more = 0;

	while(msize != 10){
		struct st_class* p = NULL;		// 난수 차단

		printf("Enter a class code > ");
		scanf("%d", &code);

		for(int i = 0; i < csize; i++){
			if(code == c[i]->code){
				p = c[i];
				break;
			}
		}

		// 과목 코드가 존재하지 않을 경우
		if(p == NULL){
			printf("No such code of class.\n");
			continue;
		}

		// 과목 코드가 중복될 경우
		int is_overlapped = 0;
		for(int j = 0; j < msize; j++){
			
			if(code == my[j]){
				printf("Overlapped class.\n");
				is_overlapped = 1;
				break;
			}
		}

		// 중복되면 다시 위로
		if(is_overlapped == 1){
			continue;
		}

		printf("[%d] %s [credit %d - %s]\n",p->code,p->name,p->unit,kname[p->grading-1]);
		my[msize] = code;
		msize++;

		// 반복 분기점
		printf("Add more?(1:Yes 2:No) > ");
		scanf("%d", &more);

		if(more == 1){
			continue;
		}else if (more == 2){
			break;
		}

	}
	return msize;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
	int total_credit = 0;

	for(int i = 0; i < msize; i++){
		for(int j = 0; j < csize; j++){
			if(my[i] == c[j]->code){
				printf("%d. [%d] %s [credit %d - %s]\n", i+1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
				total_credit += c[j]->unit;
				break;
			}
		}
	}
	printf("All : %d credits\n",total_credit);

}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){
	FILE* file = fopen("my_classes.txt","w");
	int classNum = 0;
	int total_credit = 0;
	int credit_1 = 0;	// A+~F grading
	int credit_2 = 0;	// P/F grading

	fprintf(file, "My Classes\n");

	for(int i = 0; i < msize; i++){
		for(int j = 0; j < csize; j++){
			if(my[i] == c[j]->code){
				fprintf(file, "%d. [%d] %s [credit %d - %s]\n", i+1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
				classNum++;
				total_credit += c[j]->unit;
				if(c[j]->grading == 1){
					credit_1 += c[j]->unit;
				}else if(c[j]->grading == 2){
					credit_2 += c[j]->unit;
				}
				break;
			}
		}
	}
	fprintf(file,"All : %d classes, %d credits (A+~F %d credits, P/F %d credits)\n",classNum, total_credit, credit_1, credit_2);
	fclose(file);
}
