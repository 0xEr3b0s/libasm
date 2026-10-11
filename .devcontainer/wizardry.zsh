
# Heavy Wizardry 101 - project helpers for the dev container.
#
# The shell itself (history, completion, plugins, prompt, Nebula colours)
# comes from the host dotfiles, installed by postCreateCommand.
# This file is linked to ~/.zshrc.local and sourced by the dotfiles config.

# --- Debuggers ---------------------------------------------------------------

alias gdb='gdb -q'
alias gdbm='gdb-multiarch -q'

# Débogage des exécutables x86_64 émulés par Rosetta sur Apple Silicon.
#
# Usage :
#   gdb-rosetta ./programme
#   gdb-rosetta ./programme arg1 arg2
#
# Le programme est lancé par Rosetta avec son serveur de débogage intégré.
# GDB se connecte ensuite à localhost:1234.
#
# Dans GDB, utiliser "continue" et non "run".
# Port configurable : GDB_ROSETTA_PORT=1235 gdb-rosetta ./programme

gdb-rosetta() {
    if (( $# < 1 )); then
        echo "Usage: gdb-rosetta <executable> [arguments...]" >&2
        return 2
    fi

    local prog="$1"
    shift

    if [[ "$prog" != /* ]]; then
        prog="$PWD/$prog"
    fi

    if [[ ! -f "$prog" || ! -x "$prog" ]]; then
        echo "Erreur : exécutable introuvable ou non exécutable : $prog" >&2
        return 2
    fi

    local port="${GDB_ROSETTA_PORT:-1234}"
    local target_pid
    local status

    # Vérifier que le port demandé n'est pas déjà utilisé.
    if command -v ss >/dev/null 2>&1 &&
       ss -ltn | grep -Eq "[:.]${port}[[:space:]]"; then
        echo "Erreur : le port $port semble déjà utilisé." >&2
        echo "Essaie : GDB_ROSETTA_PORT=1235 gdb-rosetta $prog" >&2
        return 1
    fi

    echo "Lancement de la cible x86_64 via Rosetta (port $port)..."

    ROSETTA_DEBUGSERVER_PORT="$port" "$prog" "$@" </dev/tty &
    target_pid=$!

    # Rosetta attend la connexion du débogueur avant l'exécution.
    sleep 1

    /usr/bin/gdb -q \
        -ex 'set architecture i386:x86-64' \
        -ex "file \"$prog\"" \
        -ex "target remote localhost:$port"

    status=$?

    # Nettoyer le processus cible à la fermeture de GDB.
    kill "$target_pid" 2>/dev/null || true
    wait "$target_pid" 2>/dev/null || true

    return "$status"
}

# --- Désassemblage multi-architecture ---------------------------------------

alias dis-x64='objdump -d -M intel'
alias dis-arm64='aarch64-linux-gnu-objdump -d'
alias dis-arm='arm-linux-gnueabihf-objdump -d'
alias dis-riscv='riscv64-linux-gnu-objdump -d'
alias dis-mips='mips-linux-gnu-objdump -d'

# --- Exécution de binaires étrangers via QEMU-user ----------------------------

alias run-arm64='qemu-aarch64 -L /usr/aarch64-linux-gnu'
alias run-arm='qemu-arm -L /usr/arm-linux-gnueabihf'
alias run-riscv='qemu-riscv64 -L /usr/riscv64-linux-gnu'
alias run-mips='qemu-mips -L /usr/mips-linux-gnu'
alias run-mipsel='qemu-mipsel -L /usr/mipsel-linux-gnu'

# --- Débogage à distance via QEMU-user ---------------------------------------
#
# Utilisation :
#   dbg-arm64 ./programme
#   gdbm ./programme
#   (gdb) target remote localhost:1234
#
# Ces fonctions sont distinctes du helper gdb-rosetta.

dbg-arm64() { qemu-aarch64 -L /usr/aarch64-linux-gnu -g 1234 "$@" }
dbg-arm()   { qemu-arm -L /usr/arm-linux-gnueabihf -g 1234 "$@" }
dbg-riscv() { qemu-riscv64 -L /usr/riscv64-linux-gnu -g 1234 "$@" }
dbg-mips()  { qemu-mips -L /usr/mips-linux-gnu -g 1234 "$@" }
