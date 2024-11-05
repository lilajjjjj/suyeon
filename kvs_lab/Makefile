# 소스 파일 및 타겟 정의
SRCS = main.c
LIBSRCS = open.c close.c put.c get.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

# 컴파일러 및 컴파일 옵션
CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

# 오브젝트 파일 및 라이브러리 파일 정의
OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LDSO = libkvs.so

# 기본 타겟: static과 dynamic을 모두 빌드
all: static dynamic

# 정적 라이브러리 및 실행 파일 생성
static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static
	@echo "Static executable $(TARG) created."

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)
	@echo "Static library $(LARS) created."

# 동적 라이브러리 및 실행 파일 생성
dynamic: $(OBJS) $(LDSO) $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LDSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS) -Wl,-rpath=.
	@echo "Dynamic executable $(TARG_DYNAMIC) created."

$(LDSO): $(LOBJS)
	$(CC) -shared -o $(LDSO) $(LOBJS)
	@echo "Shared library $(LDSO) created."

# 각 .c 파일을 .o 파일로 컴파일하는 규칙
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
	@echo "Compiled $< to $@."

# 정리(clean) 타겟: 모든 생성된 파일 제거
clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LDSO) $(TARG) $(TARG_DYNAMIC)
	@echo "Cleaned all generated files."
