Name:           kernel-lt
Version:        4.14.141
Release:        1.el7.centos
Summary:        none

License:        GPL
#URL:
Source0:        %{name}-%{version}-1.el7.centos.x86_64.tar.gz
BuildRoot:      %_topdir/BUILDROOT  

#BuildRequires:
#Requires:
%description
%prep
#%setup -q
%build

%install
tar -zxf ../SOURCES/%{name}-%{version}-1.el7.centos.x86_64.tar.gz -C $RPM_BUILD_DIR/
echo "zcw1111111"
echo $RPM_BUILD_DIR
tree -L 2 $RPM_BUILD_DIR
pwd
echo "zcw2222222"
echo  $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/boot/
mkdir -p $RPM_BUILD_ROOT/etc/
mkdir -p $RPM_BUILD_ROOT/lib/
cp -fr $RPM_BUILD_DIR/boot/* $RPM_BUILD_ROOT/boot/
cp -fr $RPM_BUILD_DIR/etc/* $RPM_BUILD_ROOT/etc/
cp -fr $RPM_BUILD_DIR/lib/* $RPM_BUILD_ROOT/lib/

%clean
#echo "rm -rf $RPM_BUILD_ROOT"
#echo "rm -rf $RPM_BUILD_ROOT"
rm -rf $RPM_BUILD_ROOT/*
rm -rf $RPM_BUILD_DIR/*

%files
/boot
/etc
/lib
%doc
%changelog
