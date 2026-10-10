FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# ============================================================================
# Heavy Wizardry 101 — dev container
#
# x86-64 + cross-compilation + reverse engineering + TCP/IP lab
# ============================================================================

# ----------------------------------------------------------------------------
# 1. Outillage de base
# ----------------------------------------------------------------------------

RUN apt-get update && apt-get install -y \
    git \
    curl \
    wget \
    make \
    build-essential \
    binutils \
    bear \
    pkg-config \
    strace \
    ltrace \
    valgrind \
    file \
    xxd \
    patchelf \
    vim \
    python3 \
    python3-pip \
    openssh-client \
    zsh \
    sudo \
    ca-certificates \
    unzip \
    ripgrep \
    fd-find \
    bat \
    fzf \
    eza \
    tmux \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------------------------------------
# 2. Compilateurs natifs x86_64 + assembleurs
# ----------------------------------------------------------------------------

RUN apt-get update && apt-get install -y \
    gcc-12 \
    g++-12 \
    gcc-14 \
    g++-14 \
    clang \
    clangd \
    clang-format \
    clang-tidy \
    clang-16 \
    clang-17 \
    llvm \
    lld \
    lldb \
    nasm \
    yasm \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------------------------------------
# 3. Chaînes de compilation croisées
# ----------------------------------------------------------------------------

RUN apt-get update && apt-get install -y \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    gcc-arm-linux-gnueabi \
    g++-arm-linux-gnueabi \
    gcc-riscv64-linux-gnu \
    g++-riscv64-linux-gnu \
    gcc-mips-linux-gnu \
    g++-mips-linux-gnu \
    gcc-mipsel-linux-gnu \
    g++-mipsel-linux-gnu \
    gcc-mips64-linux-gnuabi64 \
    g++-mips64-linux-gnuabi64 \
    gcc-mips64el-linux-gnuabi64 \
    g++-mips64el-linux-gnuabi64 \
    gdb \
    gdb-multiarch \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------------------------------------
# 4. Émulation + réseau + DNS + capture
#
# - qemu-user / qemu-user-static : exécution de binaires cross-arch
# - iproute2 : ip / ss
# - dnsutils : dig
# - tcpdump : capture CLI
# - tshark : Wireshark en CLI
# - wireshark : analyse graphique des captures
# ----------------------------------------------------------------------------

RUN apt-get update && apt-get install -y \
    qemu-user \
    qemu-user-static \
    binfmt-support \
    netcat-openbsd \
    socat \
    tcpdump \
    tshark \
    wireshark \
    iproute2 \
    iputils-ping \
    dnsutils \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------------------------------------
# 5. Java + Ghidra
#
# Ghidra 12.1.4 est utilisé ici.
# Le release officiel demande un JDK 25 64-bit.
# ----------------------------------------------------------------------------

ARG GHIDRA_VERSION=12.1.4
ARG GHIDRA_DATE=20260921
ARG GHIDRA_SHA256=ddac49f903da9d5bac833e5cc79395098b9c33cfd3279be5f31bd00387d2d4db

RUN apt-get update && apt-get install -y \
    openjdk-25-jdk \
    && rm -rf /var/lib/apt/lists/*

ENV JAVA_HOME=/usr/lib/jvm/java-25-openjdk-amd64
ENV GHIDRA_HOME=/opt/ghidra
ENV PATH="${GHIDRA_HOME}:${PATH}"

RUN wget -q \
        "https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_${GHIDRA_VERSION}_build/ghidra_${GHIDRA_VERSION}_PUBLIC_${GHIDRA_DATE}.zip" \
        -O /tmp/ghidra.zip \
    && echo "${GHIDRA_SHA256}  /tmp/ghidra.zip" | sha256sum -c - \
    && unzip -q /tmp/ghidra.zip -d /opt \
    && mv "/opt/ghidra_${GHIDRA_VERSION}_PUBLIC" "${GHIDRA_HOME}" \
    && rm -f /tmp/ghidra.zip \
    && chmod +x "${GHIDRA_HOME}/ghidraRun" \
    && ln -sf "${GHIDRA_HOME}/ghidraRun" /usr/local/bin/ghidra

# ----------------------------------------------------------------------------
# 6. Utilisateur de développement + shell
# ----------------------------------------------------------------------------

RUN useradd -m -s /usr/bin/zsh dev \
    && echo "dev ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/dev \
    && chmod 0440 /etc/sudoers.d/dev

# Shell config comes from the host dotfiles (postCreateCommand runs
# ~/.dotfiles/install.sh --minimal); project helpers live in wizardry.zsh.

# ----------------------------------------------------------------------------
# 7. Workspace
# ----------------------------------------------------------------------------

WORKDIR /workspace

USER dev

CMD ["/bin/zsh"]
