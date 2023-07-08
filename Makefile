CC := g++
CFLAGS := -std=c++11 -Wall
LDFLAGS := -lcurl

# Diretórios dos arquivos de origem e destino
SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin
DATADIR := data

# Nome do executável
TARGET := app

# Objetos necessários para compilar o programa
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Compilação do programa
$(BINDIR)/$(TARGET): $(OBJS) $(OBJDIR)/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(OBJDIR)/main.o -o $@

# Compilação dos arquivos de origem
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Compilação do arquivo main.cpp
$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(TARGET)

# Execução do programa
run:
	$(BINDIR)/$(TARGET)
