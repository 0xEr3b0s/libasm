# Minimal zsh config for the Heavy Wizardry 101 dev container.
# Standalone — depends on nothing from the host dotfiles.

# History
HISTFILE=~/.zsh_history
HISTSIZE=10000
SAVEHIST=10000
setopt SHARE_HISTORY HIST_IGNORE_ALL_DUPS HIST_IGNORE_SPACE

# Behaviour
setopt AUTO_CD INTERACTIVE_COMMENTS
bindkey -e

# Completion
autoload -Uz compinit && compinit
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Za-z}'
zstyle ':completion:*' menu select

# Plugins (installed by apt in the Dockerfile — system paths, not XDG)
source /usr/share/zsh-autosuggestions/zsh-autosuggestions.zsh 2>/dev/null
source /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh 2>/dev/null

# Prompt — simple, shows path and git branch, no external tool
autoload -Uz vcs_info
precmd() { vcs_info }
zstyle ':vcs_info:git:*' formats ' %F{magenta}(%b)%f'
setopt PROMPT_SUBST
PROMPT='%F{blue}%~%f${vcs_info_msg_0_} %F{green}❯%f '

# Aliases
alias ls='ls --color=auto'
alias ll='ls -lah'
alias gs='git status -sb'
alias mk='make'
alias gdb='gdb -q'

# --- Heavy Wizardry 101 : multi-architecture helpers ------------------------
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
