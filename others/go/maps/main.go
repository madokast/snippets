package main

func main() {
	var m []map[string]string = nil
	for k, v := range m {
		println(k, v)
	}
	println("iter a nil map is ok")
}
