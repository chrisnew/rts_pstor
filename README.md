# rts_pstor

Linux driver for Realtek PCI-Express card reader chip.

## install

Clone this repository into `/usr/src/rts_pstor-1.11` and use `dkms install` to install the module with dkms.

```bash
# switch into /usr/src
cd /usr/src

# clone this repository
git clone https://github.com/chrisnew/rts_pstor.git rts_pstor-1.11

# compile and install through dkms
dkms install rts_pstor/1.11

# load the module
modprobe rts_pstor
```

