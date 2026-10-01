# !/bin/bash
# Verifica se o nome foi fornecido

if [ $# -lt 1 ]; then
    echo "Uso: $0 <nome_do_programa>"
    exit 1
fi

NAME="$1"

# Detecta a extensão
if [ -f "${NAME}.cc" ]; then
    SOURCE="${NAME}.cc"
    COMPILER="g++"
elif [ -f "${NAME}.cpp" ]; then
    SOURCE="${NAME}.cpp"
    COMPILER="g++"
elif [ -f "${NAME}.c" ]; then
    SOURCE="${NAME}.c"
    COMPILER="gcc"
else
    echo "Erro: não encontrei ${NAME}.c, ${NAME}.cc ou ${NAME}.cpp"
    exit 1
fi

echo "Compilando ${SOURCE}..."

$COMPILER -Wall "$SOURCE" \
    $(globes-config --cflags) \
    $(globes-config --libs) \
    -O3 \
    -o "$NAME"

# Só executa se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo "Erro na compilação."
    exit 1
fi

echo "Executando ./${NAME}"
echo

./"$NAME"