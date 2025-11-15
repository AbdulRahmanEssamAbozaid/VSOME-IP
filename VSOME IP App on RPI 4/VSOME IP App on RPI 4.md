# 📦 Adding vSomeIP to Yocto Image (Recipe + Integration Guide)

Below is the full procedure for adding **vSomeIP** to your Yocto image using your custom layer **meta-ota**, including the recipe content, directory structure, and how it becomes part of the final Raspberry Pi image.

---

## 📝 1. Recipe Content (vsomeip_3.4.10.bb)

Place this file inside:

```
meta-ota/recipes-ota/vsomeip/vsomeip_3.4.10.bb
```

Recipe content:

```
SUMMARY = "COVESA vsomeip implementation"
DESCRIPTION = "Implementation of the Scalable middleware SOME/IP"
HOMEPAGE = "https://github.com/COVESA/vsomeip"
LICENSE = "MPL-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=9741c346eef56131163e13b9db1241b3"

SRC_URI = "git://github.com/COVESA/vsomeip.git;branch=master;protocol=https"
SRCREV = "f58ba578c8c04e02dcf08d3ebcb9a71ca1e203ea"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

DEPENDS = "boost"

EXTRA_OECMAKE = " \
    -DENABLE_SIGNAL_HANDLING=1 \
    -DUSE_EXTERNAL_JSON=0 \
"

FILES:${PN} += " \
    ${bindir} \
    ${libdir} \
"

FILES:${PN} += " \
    ${sysconfdir}/vsomeip \
    /usr/etc/vsomeip \
"
```

---

## 📂 2. Layer Structure (Verified Working Tree)

Your layer must look like this:

```
meta-ota/
├── conf
│   └── layer.conf
├── COPYING.MIT
├── README
├── recipes-example
│   └── example
│       └── example_0.1.bb
└── recipes-ota
    └── vsomeip
        └── vsomeip_3.4.10.bb
```

---

## 🔗 3. Adding Layer to Build

From your Yocto build directory:

```
bitbake-layers add-layer ../layers/meta-ota
```

Confirm using:

```
bitbake-layers show-layers
```

You should see:

```
meta-ota  =>  /home/abdo/yocto/layers/meta-ota
```

---

## 🏗 4. Include vSomeIP in Your Image

Inside your **core-image-abozaid.bb** add:

```
IMAGE_INSTALL:append = " vsomeip "
```

Then build:

```
bitbake core-image-abozaid
```

After flashing the image on Raspberry Pi, the following will appear on the target:

```
/usr/bin/vsomeip*
/usr/lib/libvsomeip.so*
/etc/vsomeip/
/usr/etc/vsomeip/
```

This verifies vSomeIP is installed successfully.

---

# vSomeIP Simple Client/Server Demo on Raspberry Pi (Yocto Image)

This project demonstrates how to run a minimal **vSomeIP client/server application** directly **inside the Yocto image** on a Raspberry Pi — without rebuilding the whole image each time.

It includes:

* Simple server that offers a SOME/IP service.
* Simple client that waits for service availability then sends a request.
* Successful message exchange used to validate vSomeIP functionality.

---

## 📌 Project Structure

```
simple/
├── client.cpp
├── server.cpp
├── vsomeip.json
└── CMakeLists.txt
```

---

## ⚙️ Build Instructions (Inside the Yocto Image)

1. Copy the `simple/` folder to the Raspberry Pi image.
2. Enter the directory:

```
cd ~/simple
```

3. Create build folder:

```
mkdir build && cd build
```

4. Build the application using the vSomeIP library already installed in the image:

```
cmake ..
make
```

This generates:

```
server
client
```

---

## 🚀 Run Instructions

### **1. Start the Server**

```
./server
```

Expected output:

```
[SERVER] Offering service...
[SERVER] Got request: Hello from Client!
```

### **2. Start the Client**

```
./client
```

Expected output:

```
[CLIENT] Registered with routing.
[CLIENT] Service is now AVAILABLE! Sending request...
[CLIENT] Received RESPONSE: Hello from Server!
```

---

## 🧠 Server Logic (server.cpp)

* Initializes vSomeIP
* Offers service **0x1234 / 0x5678**
* Handles method **0x0421**
* Prints received request
* Replies with "Hello from Server!"

---

## 🧠 Client Logic (client.cpp)

* Waits for registration
* Subscribes to service availability
* Only sends request *after* service becomes available
* Sends "Hello from Client!"
* Receives server response

This solves the common issue:

```
Service not available. instance=5678
```

by ensuring request is sent *after* `ON_AVAILABLE`.

---

## 🗂 vSomeIP Configuration (vsomeip.json)

A minimal configuration file placed next to the binaries:

```
{
    "unicast": "127.0.0.1",
    "logging": {
        "level": "info",
        "console": "true"
    },
    "applications": [
        { "name": "client-sample", "id": "0x101" },
        { "name": "service-sample", "id": "0x100" }
    ],
    "services": []
}
```

---

## 🛠 CMakeLists.txt

```
cmake_minimum_required(VERSION 3.10)
project(simple_vsomeip)

set(CMAKE_CXX_STANDARD 14)
find_package(vsomeip3 REQUIRED)

add_executable(server server.cpp)
target_link_libraries(server vsomeip3)

add_executable(client client.cpp)
target_link_libraries(client vsomeip3)
```

---

## ✅ Summary

This demo validates:

* vSomeIP is installed correctly in the Yocto image.
* Client and server communicate via SOME/IP.
* Configuration works.
* No image rebuild is needed.

You're now ready to extend this into:

* ECU sensors simulation
* AUTOSAR-style service communication
* Multi-node functional testing

If you want, I can generate the **entire code folder** inside another canvas page ready to upload to GitHub.

---

## 🧱 Architecture Overview

```
   +----------------------+           SOME/IP            +----------------------+
   |     Client App      | ---------------------------> |     Server App       |
   |  Request Service    | <--------------------------- |  Offer Service       |
   |  Send METHOD_ID     | ---------------------------> |  Handle Request      |
   |  Receive Response   | <--------------------------- |  Send Response       |
   +----------------------+                              +----------------------+
```

---

## 🔄 Communication Flow (Step-by-Step)

```
Client                           Server
-----------------------------------------------------------
Start client
 ↓
Wait for registration-----------→ Routing Manager
 ↓
Wait for ON_AVAILABLE           ← Offer service (1234/5678)
 ↓
Send request (METHOD_ID) -------→ Handle request
                                  Process & prepare response
Receive response  ←-------------- Send "Hello from Server"
```

---

## 🧪 Commands Verification Checklist

Use these commands inside the Raspberry Pi image to verify that vSomeIP works properly:

### ✅ 1. Check that vSomeIP is installed

```
ls /usr/lib | grep vsomeip
```

### ✅ 2. Check that config directory exists

```
ls /usr/etc/vsomeip
```

### ✅ 3. Check routing manager socket

```
ls -la /tmp | grep vsomeip
```

Should show something like:

```
/tmp/vsomeip-0
```

### ✅ 4. Run server

```
./server
```

### ✅ 5. Run client

```
./client
```

If both run without "Service not available" issues → Everything works.

---

## 🐞 Debugging vSomeIP (Advanced)

### 🔍 Enable verbose logs

Edit your `vsomeip.json`:

```json
{
  "logging": {
    "level": "debug",
    "console": "true"
  }
}
```

Restart server & client → now you see all routing, connections, and SD messages.

---

### 🔍 Check routing manager status

```
ls -la /tmp/vsomeip-0
```

If this socket is missing → routing manager did not start.

---

### 🔍 Check internal threads

Use:

```
top -H
```

You should see threads:

* `_m_dispatch`
* `_io00`
* `_io01`
* `_shutdown`

---

### 🔍 Show active SOME/IP traffic

```
vsomeipctl
```

(available in modern vsomeip builds)

---

## 🔥 Common Errors & Fixes

### ❌ **Service not available**

**Cause:** Client sends request before server is available.

**Fix:** Only send request after `ON_AVAILABLE` callback.

---

### ❌ "rejecting service registration"

**Cause:** You accidentally ran the *same* app name twice.

**Fix:** Each vSomeIP app **must have a unique name & ID**:

```
client-sample → 0x101
service-sample → 0x100
```

---

### ❌ Hanging or weird behavior

**Cause:** Old UNIX sockets were not removed.

**Fix:**

```
rm -rf /tmp/vsomeip-*
```

---

## 📁 Understanding /tmp/vsomeip-* Sockets

vSomeIP uses **UNIX domain sockets** for internal routing.

When server starts, it creates:

```
/tmp/vsomeip-0      ← routing manager
/tmp/vsomeip-100    ← server local socket
```

When client connects, it creates:

```
/tmp/vsomeip-101    ← client local socket
```

If you stop apps abnormally → these sockets remain and cause corruption.

Always clear them before tests:

```
rm -rf /tmp/vsomeip-*
```

---

