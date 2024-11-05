# 변수 정의
SRCS = static_main.c
LIBSRCS = open.c close.c put.c get.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

# 오브젝트 파일 및 라이브러리 파일 변수 정의
OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LDSO = libkvs.so

# 기본 빌드 타겟
all: static dynamic

# 정적 라이브러리 빌드 및 정적 실행 파일 생성
static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static
	@echo "Static executable $(TARG) created."

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)
	@echo "Static library $(LARS) created."

# 동적 라이브러리 빌드 및 동적 실행 파일 생성
dynamic: $(OBJS) $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LDSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS)
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

