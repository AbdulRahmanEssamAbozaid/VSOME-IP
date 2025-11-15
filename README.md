# VSOMEIP on Raspberry Pi (Yocto) — Full Setup Guide

This README provides a **clean, professional, GitHub‑ready guide** for installing, configuring, and running **VSOMEIP** on a Raspberry Pi running a **Yocto-based Linux image**. It includes:

* Full installation steps
* Storage expansion & fixing low‑space issues
* Installing packages without rebuilding the Yocto image
* How to find missing packages & deploy them
* How to run examples on the Raspberry Pi

---

# 🚀 1. Install VSOMEIP on Raspberry Pi (Yocto)

### **1.1 Update Yocto Package Feeds (if configured)**

If your Yocto image supports package management with `opkg`:

```bash
opkg update
```

### **1.2 Install Dependencies**

VSOMEIP requires:

* `boost`
* `cmake`
* `gcc/g++`
* `cmake`
* `asio` (depending on VSOMEIP version)

Install using:

```bash
opkg install boost boost-dev cmake gcc g++
```

If any package is missing → see Section **4**.

### **1.3 Clone VSOMEIP Inside Raspberry Pi**

```bash
git clone https://github.com/GENIVI/vsomeip.git
cd vsomeip
```

### **1.4 Configure the Build**

```bash
mkdir build
cd build
cmake ..
```

### **1.5 Build & Install**

```bash
make
sudo make install
```

---

# ⚠️ 2. Fixing "No Space Left" During `make install`

Low storage is very common on Yocto images. Here is the full solution.

## **2.1 Clean Temporary Storage**

```bash
rm -rf /tmp/*
rm -rf /var/tmp/*
```

## **2.2 Clean Logs**

```bash
journalctl --vacuum-size=50M
rm -rf /var/log/*.gz
rm -rf /var/log/*.1
```

## **2.3 Expand the RootFS Partition** (Recommended)

### **Step 1 — Open fdisk:**

```bash
fdisk /dev/mmcblk0
```

### **Step 2 — Delete & recreate the root partition**

Do **not** touch partition `p1` (boot partition).

Delete partition:

```
d
2
```

Recreate it:

```
n
p
2
<press enter>
<press enter>
```

Save:

```
w
```

Reboot:

```bash
reboot
```

### **Step 3 — Resize the filesystem**

```bash
resize2fs /dev/mmcblk0p2
```

Now you have the full SD card available.

---

# 📦 3. Installing Packages Without Rebuilding Yocto Image

Often a Yocto image doesn't include needed packages like `boost-dev` or `cmake`. You **don’t need to rebuild the whole image** — use one of these methods:

---

## ✔ Method 1 — Install IPK Packages via SCP (Recommended)

You can copy `.ipk` packages from host → Raspberry Pi:

### **3.1 Find packages on host (Yocto build machine)**

Your Yocto build stores packages here:

```
<yocto_build>/tmp/deploy/ipk/
```

Inside you’ll find architecture folders like:

* `aarch64`
* `armv7vet2hf-neon`
* `all`

Example:

```
cd ~/yocto/poky/build/tmp/deploy/ipk/aarch64
```

---

### **3.2 Copy package to Raspberry Pi**

```bash
scp boost-dev_1.76.0-r0_aarch64.ipk root@<rpi-ip>:/home/root/
```

### **3.3 Install package on RPI**

```bash
opkg install /home/root/boost-dev_*.ipk
```

---

## ✔ Method 2 — Use SSHFS to Mount Raspberry Pi Filesystem

```bash
sudo apt install sshfs
mkdir rpi
sshfs root@<rpi-ip>:/ rpi
```

Now you can drag‑and‑drop files into `rpi/`.

---

# 🔍 4. How to Find Missing Packages

When CMake fails, it usually shows messages like:

```
Could NOT find Boost
Could NOT find asio
```

To check what packages exist on your image:

```bash
opkg list
```

To search:

```bash
opkg list | grep boost
```

If missing → get the `.ipk` from **Yocto deploy directory** (Section 3.1).

---

# ▶ 5. Running VSOMEIP Examples

After installing VSOMEIP:

### **5.1 Create Config File**

`vsomeip.json`:

```json
{
  "unicast" : "<rpi-ip>",
  "logging" : { "level" : "debug" }
}
```

### **5.2 Export Environment Variables**

```bash
export VSOMEIP_CONFIGURATION=/home/root/vsomeip.json
export VSOMEIP_APPLICATION_NAME=service
```

### **5.3 Run the Service**

```bash
./example-service
```

### **5.4 Run the Client**

```bash
./example-client
```

---

# 🎯 Final Notes

* No need to rebuild the whole Yocto image for every missing library.
* Using `.ipk` packages from the host system is the fastest method.
* Expanding the SD card partition permanently prevents build failures.
* VSOMEIP runs smoothly once all dependencies are installed.

---