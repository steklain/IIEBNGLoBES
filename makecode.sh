# !/bin/bash
# Verifica se o nome foi fornecido

if [ $# -lt 1 ]; then
    echo "Uso: $0 <nome_do_programa>"
    exit 1
fi

NAME="$1"
SOURCE="${NAME}.cc"

g++ ${SOURCE} -o ${NAME} `/opt/globes/bin/globes-config --libs --include`