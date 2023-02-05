int func(int wild_idx, int str_idx) {
	int &ret = dp[wild_idx][str_idx];
	if (ret != -1) return ret;
	while (wild_idx < wild_len && str_idx < str_len && (s1[wild_idx] == s2[str_idx] || s1[wild_idx] == '?')) {
		return ret = func(wild_idx + 1, str_idx + 1);
	}

	if (wild_idx == wild_len) {
		if (str_idx == str_len) return ret = 1;
		return ret = 0;
	}

	if (s1[wild_idx] == '*') {
		if (func(wild_idx + 1, str_idx) || (func(wild_idx, str_idx + 1) && str_idx < str_len))
			return ret = 1;
	}

	return ret = 0;
}