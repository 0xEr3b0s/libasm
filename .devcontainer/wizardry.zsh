# Heavy Wizardry 101 - project helpers for the dev container.
# The shell itself (history, completion, plugins, prompt, Nebula colours) comes
# from the host dotfiles, mounted read-only at ~/.dotfiles and installed by
# postCreateCommand. postCreateCommand links this file to ~/.zshrc.local, which
# the dotfiles zsh config sources last.

alias gdb='gdb -q'

# --- multi-architecture helpers ----------------------------------------------
# Désassemblage par arche (objdump croisé fourni par les paquets gcc-*-cross)
alias dis-x64='objdump -d -M intel'
alias dis-arm64='aarch64-linux-gnu-objdump -d'
alias dis-arm='arm-linux-gnueabihf-objdump -d'
alias dis-riscv='riscv64-linux-gnu-objdump -d'
alias dis-mips='mips-linux-gnu-objdump -d'

# gdb unique pour toutes les arches
alias gdbm='gdb-multiarch -q'

# Exécution d'un binaire étranger sous QEMU-user, avec le sysroot de l'arche.
#   run-arm64 ./a.out   /   run-riscv ./a.out   etc.
alias run-arm64='qemu-aarch64 -L /usr/aarch64-linux-gnu'
alias run-arm='qemu-arm -L /usr/arm-linux-gnueabihf'
alias run-riscv='qemu-riscv64 -L /usr/riscv64-linux-gnu'
alias run-mips='qemu-mips -L /usr/mips-linux-gnu'
alias run-mipsel='qemu-mipsel -L /usr/mipsel-linux-gnu'

# Débogage à distance sous QEMU : lance le binaire en attente sur :1234,
# puis « gdbm <bin> » et, dans gdb, « target remote :1234 ».
#   dbg-arm64 ./a.out
dbg-arm64() { qemu-aarch64 -L /usr/aarch64-linux-gnu -g 1234 "$@" }
dbg-arm()   { qemu-arm     -L /usr/arm-linux-gnueabihf -g 1234 "$@" }
dbg-riscv() { qemu-riscv64 -L /usr/riscv64-linux-gnu  -g 1234 "$@" }
dbg-mips()  { qemu-mips    -L /usr/mips-linux-gnu      -g 1234 "$@" }
