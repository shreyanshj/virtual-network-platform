include_recipe 'virtual-network-platform::tuntap-device'
if node['package_openvswitch']
  include_recipe 'virtual-network-platform::openvswitch-switch'
else
  include_recipe 'virtual-network-platform::build-openvswitch'
end
include_recipe 'virtual-network-platform::create-switch-instance'
include_recipe 'virtual-network-platform::getting-the-source-code'
if node['virtual_network_agent']['vxlan_adapter'] == 'linux_kernel'
  include_recipe 'virtual-network-platform::linux-kernel-vxlan'
else
  include_recipe 'virtual-network-platform::vxlan-tunnel-end-point'
end
include_recipe 'virtual-network-platform::rbenv-ruby-and-bundler'
include_recipe 'virtual-network-platform::virtual-network-agent'
include_recipe 'virtual-network-platform::bash-aliases'
