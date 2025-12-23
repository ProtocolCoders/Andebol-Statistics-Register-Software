# Nome do executável
EXECUTAVEL = andebol

# Compilador
CC = gcc

# Flags de compilação
# -Wall: Ativa todos os avisos
# -g: Adiciona informação de debug
# -Iinclude: Adiciona o diretório 'include' à lista de diretórios a procurar por ficheiros de cabeçalho
CFLAGS = -Wall -Wextra -g -Iinclude -fstack-protector-strong -Wformat-security

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Encontra todos os ficheiros .c na pasta src
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Gera os nomes dos ficheiros objeto (.o) correspondentes na pasta obj
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Caminho completo para o executável
TARGET = $(BINDIR)/$(EXECUTAVEL)

# Regra principal: é executada por defeito com 'make'
all: $(TARGET)

# Regra para ligar os ficheiros objeto e criar o executável final
$(TARGET): $(OBJECTS)
	@if not exist $(BINDIR) mkdir $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo Executável '$(TARGET)' criado com sucesso.

# Regra para compilar cada ficheiro fonte (.c) num ficheiro objeto (.o)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar o programa
run: $(TARGET)
	@echo A executar o programa...
	$(TARGET)

# Regra para limpar os ficheiros gerados pela compilação
clean:
	@if exist $(BINDIR) ( rmdir /s /q $(BINDIR) && echo Diretório '$(BINDIR)' removido. ) else ( echo Diretório '$(BINDIR)' não existe. )
	@if exist $(OBJDIR) ( rmdir /s /q $(OBJDIR) && echo Diretório '$(OBJDIR)' removido. ) else ( echo Diretório '$(OBJDIR)' não existe. )

# Targets que não são ficheiros
.PHONY: all clean run