CC=gcc
CCFLAGS=-Wall

SOULANG_SRC=$(shell find src/ -name *.c)
SOULANG_OUT=$(patsubst src/%.c, out/%.o, $(SOULANG_SRC))

SVM_SRC =	$(shell find svm/src/ -name *.c)
SVM_OUT =   $(patsubst svm/src/%.c, svm/out/%.o, $(SVM_SRC))

$(SVM_OUT):    svm/out/%.o: 	svm/src/%.c
	@mkdir -p $(dir $@)
	@echo " CC     $@"
	@$(CC) -c $(CCFLAGS) $(patsubst svm/out/%.o, svm/src/%.c, $@) -o $@

$(SOULANG_OUT):out/%.o:         src/%.c
	@mkdir -p $(dir $@)
	@echo " CC     $@"
	@$(CC) -c $(CCFLAGS) $(patsubst out/%.o, src/%.c, $@) -o $@

build-svm: $(SVM_OUT)
	@echo "Build libs..."
	@./build-libs.sh
	@$(CC) outlibs/*.o $(CCFLAGS) $(SVM_OUT) -o souvm
	@echo "done (./svm)"
build: $(SOULANG_OUT)
	@echo "Build libs..."
	@./build-libs.sh
	@echo "Build..."
	@$(CC) outlibs/*.o $(CCFLAGS) $(SOULANG_OUT) -o soulang
	@echo "done (./soulang)"
clean:
	@rm -r svm/out
	@mkdir svm/out
	@rm -r out
	@mkdir out