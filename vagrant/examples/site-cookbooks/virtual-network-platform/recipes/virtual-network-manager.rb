log 'install prerequisites for trema... wait a few minutes.'
%w{ gcc make git libpcap-dev libsqlite3-dev libglib2.0-dev }.each do | package_name |
  package package_name
end

log 'build trema... wait a few minutes.'
bash "build-trema" do
  cwd "/home/vagrant/virtual-network-platform/trema"
  user "vagrant"
  code <<-'EOT'
    bundle config --local path vendor/bundle &&
    bundle install &&
    ./build.rb &&
    mkdir -p tmp/log tmp/sock tmp/pid
  EOT
  environment 'HOME' => "/home/vagrant" #
end

log 'install prerequisites for virtual network platform... wait a few minutes.'
%w{ libcurl4-gnutls-dev libjson0-dev libmysqlclient-dev }.each do | package_name |
  package package_name
end

ovs_version_code = node['ovs_version_code'] || '0x020100'

bash "build-virtual-network-manager (OVS_VERSION_CODE=#{ ovs_version_code })" do
  cwd "/home/vagrant/virtual-network-platform/virtual_network_manager/src"
  user "vagrant"
  code "make OVS_VERSION_CODE=#{ ovs_version_code }"
end

bash "setup init script (virtual_network_manage)" do
  user "root"
  code <<-'EOT'
    cp /home/vagrant/virtual-network-platform/virtual_network_manager/init/virtual_network_manager /etc/init.d
  EOT
  not_if { ::File.exists?("/etc/init.d/virtual_network_manage") }
end

bash "setup init script (trema)" do
  user "root"
  code <<-'EOT'
    cp /home/vagrant/virtual-network-platform/virtual_network_manager/init/trema /etc/init.d
  EOT
  not_if { ::File.exists?("/etc/init.d/trema") }
end

bash "setup configuration files (virtual_network_manager)" do
  user "root"
  code <<-'EOT'
    cp /home/vagrant/virtual-network-platform/virtual_network_manager/config/virtual_network_manager /etc/default &&
    sed -i -e "s/^VIRTUAL_NETWORK_MANAGER_DIR=.*$/VIRTUAL_NETWORK_MANAGER_DIR=\"\/home\/vagrant\/virtual-network-platform\/virtual_network_manager\/src\"/" /etc/default/virtual_network_manager &&
    chown root.root /etc/default/virtual_network_manager &&
    chmod 600 /etc/default/virtual_network_manager
  EOT
  not_if { ::File.exists?("/etc/default/virtual_network_manage") }
end

bash "setup configuration files (trema)" do
  user "root"
  code <<-'EOT'
    cp /home/vagrant/virtual-network-platform/virtual_network_manager/config/trema /etc/default
    sed -i -e "s/^TREMA_HOME=.*$/TREMA_HOME=\"\/home\/vagrant\/virtual-network-platform\/trema\"/" /etc/default/trema
  EOT
  not_if { ::File.exists?("/etc/default/trema") }
end

service "trema" do
  supports :status => true, :restart => true
  action [ :enable, :start ]
end

service "virtual_network_manager" do
  supports :status => true, :restart => true
  action [ :enable, :start ]
end

directory "/home/vagrant/bin" do
  owner "vagrant"
  group "vagrant"
  mode 0755
  action :create
end

template "/home/vagrant/bin/slice" do
  source "slice.erb"
  mode 0755
  owner "vagrant"
  group "vagrant"
  variables :home_vagrant => "/home/vagrant"
end

bash "examples" do
  cwd "/home/vagrant"
  user "vagrant"
  code "ln -s virtual-network-platform/doc/api/examples/curl examples"
  not_if { ::File.exists?("/home/vagrant/examples") }
end
