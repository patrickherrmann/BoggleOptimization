#!/usr/bin/env ruby

untrimmed = File.new(ARGV[0], "r")
trimmed = File.new(ARGV[1], "w")

def good(word)
   return false if word.length < 3
   "qzxjkvwyfhbu".each_char do |b|
      return false if word.include? b
   end
   true
end

untrimmed.each do |line|
   word = line.chomp.downcase
   if good word
      trimmed.write word + "\n"
   end
end
