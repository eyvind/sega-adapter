# frozen_string_literal: true

require 'rake/clean'
require 'rake/loaders/makefile'

CC = 'xc8-cc'
CFLAGS = '-mcpu=16f1847'

target_file = 'sega-adapter.hex'
source_files = Rake::FileList[
  'sega-adapter.c',
  'controller.c',
  'joy2b.c',
  'snack.c',
]
object_files = source_files.ext('.p1')

task default: target_file

# Build and link the target file with the object files in one step
rule(/{#{[target_file, *object_files].join('|')}}/) do
  sh CC, *CFLAGS, '-o', target_file, *source_files
end
# Make the target file inherit the object files' dependencies
file target_file => object_files
CLOBBER << target_file

# Rake complains if it doesn't know how to build the object files
rule '.p1' => '.c' do |t|
  sh CC, *CFLAGS, '-c', t.source
end

# Import dependency files
Rake.application.add_loader('d', Rake::MakefileLoader.new)
Rake::FileList['*.d'].each do |dep|
  import dep
end

CLEAN.include('*.cmf', '*.d', '*.elf', '*.hxl', '*.o', '*.p1',
              '*.s', '*.sdb', '*.sym', 'startup.*')
