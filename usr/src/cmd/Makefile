include ../../../tools/common.mk
include ../../../tools/user.mk

SOURCEDIR=.
BUILDDIR=.
SOURCES:=$(wildcard $(SOURCEDIR)/*.c)
OBJ:=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
CFLAGS += -nostdinc -I ../../include
CFLAGS += -nostdlib -DCRUTCH=1
# LDFLAGS += -L../libc -lc
STARTUP=../libc/csu/crt0.o


# -include *.d

CMDS=\
ac \
accton \
ar \
arcv \
at \
atrun \
basename \
cal \
calendar \
cat \
cb \
cc \
checkeq \
chgrp \
chmod \
chown \
clri \
cmp \
col \
comm \
cp \
cron \
crypt \
cu \
date \
dcheck \
dd \
deroff \
df \
diff \
diff3 \
diffh \
dmesg \
du \
dump \
dumpdir \
echo \
ed \
fgrep \
file \
find \
fsck \
getty \
graph \
grep \
icheck \
init \
iostat \
join \
kill \
ld \
ln \
login \
look \
ls \
mail \
makekey \
mesg \
mkdir \
mkfs \
mknod \
mount \
mv \
ncheck \
newgrp \
nice \
nm \
od \
osh \
passwd \
pr \
prof \
ps \
pstat \
ptx \
pwd \
quot \
random \
ranlib \
restor \
rev \
rm \
rmdir \
sa \
size \
sleep \
sort \
sp \
spline \
split \
strip \
stty \
su \
sum \
sync \
tabs \
tail \
tc \
tee \
test \
time \
tk \
touch \
tr \
tsort \
tty \
umount \
uniq \
units \
update \
vpr \
wall \
wc \
who \
write \
yes

# OBJECTS := $(C_SOURCES:.c=.o) $(S_SOURCES:.s=.o)

#%: %.o
#	$(LD) $(LDFLAGS) -o $@ $^  -L../libc -lc

all: $(OBJ) $(CMDS) 

clean:
	rm -f $(CMDS) $(OBJ) *.d

xtroff:
	cd troff ; $(MAKE)
