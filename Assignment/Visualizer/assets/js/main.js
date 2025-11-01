(function () {
	const loadScript = (src) =>
		new Promise((resolve, reject) => {
			const script = document.createElement("script");
			script.src = src;
			script.async = true;
			script.onload = () => resolve();
			script.onerror = () =>
				reject(new Error(`Không tải được script: ${src}`));
			document.head.appendChild(script);
		});

	const ensureLibrary = async (checker, fallbackSrc, label) => {
		if (checker()) {
			return checker();
		}
		if (fallbackSrc) {
			try {
				await loadScript(fallbackSrc);
			} catch (error) {
				throw new Error(
					`Không tải được thư viện ${label}: ${error.message}`
				);
			}
		}
		const lib = checker();
		if (!lib) {
			throw new Error(`Thư viện ${label} chưa khả dụng.`);
		}
		return lib;
	};

	const ensureCanvg = (() => {
		let loader = null;
		return async () => {
			if (window.canvg?.Canvg) {
				return window.canvg.Canvg;
			}
			if (!loader) {
				loader = loadScript(
					"https://cdn.jsdelivr.net/npm/canvg@3.0.10/lib/umd.min.js"
				)
					.then(() => window.canvg?.Canvg || null)
					.catch((error) => {
						console.error(error);
						return null;
					});
			}
			const result = await loader;
			if (!result) {
				throw new Error("Không thể tải thư viện canvg");
			}
			return result;
		};
	})();

	const init = async () => {
		const numberInput = document.getElementById("number-input");
		const generateBtn = document.getElementById("generate-btn");
		const copyBtn = document.getElementById("copy-ascii-btn");
		const downloadBtn = document.getElementById("download-img-btn");
		const statusText = document.getElementById("status-text");
		const asciiPanel = document.getElementById("ascii-panel");
		const asciiText = document.getElementById("ascii-text");
		const asciiEmpty = document.getElementById("ascii-empty");
		const sampleBtn = document.getElementById("sample-btn");
		const zoomInBtn = document.getElementById("zoom-in");
		const zoomOutBtn = document.getElementById("zoom-out");
		const resetViewBtn = document.getElementById("reset-view");
		const svgElement = document.getElementById("tree-svg");

		const setStatus = (message, type = "info") => {
			statusText.textContent = message || "";
			statusText.className = `mt-2 text-sm ${
				type === "error" ? "text-rose-300" : "text-slate-300"
			}`;
		};

		let d3;
		let svgPanZoom;
		try {
			d3 = await ensureLibrary(
				() => window.d3,
				"https://cdnjs.cloudflare.com/ajax/libs/d3/7.9.0/d3.min.js",
				"D3"
			);
			svgPanZoom = await ensureLibrary(
				() => window.svgPanZoom,
				"https://cdnjs.cloudflare.com/ajax/libs/svg-pan-zoom/3.6.1/svg-pan-zoom.min.js",
				"svg-pan-zoom"
			);
		} catch (libraryError) {
			console.error(libraryError);
			setStatus(
				"Không thể tải thư viện trực quan hóa. Vui lòng kiểm tra kết nối mạng và thử lại.",
				"error"
			);
			generateBtn.disabled = true;
			copyBtn.disabled = true;
			downloadBtn.disabled = true;
			return;
		}

		const linksGroup = d3.select("#tree-links");
		const nodesGroup = d3.select("#tree-nodes");

		let panZoomInstance = null;
		let currentRoot = null;
		let currentAscii = "";

		class TreeNode {
			constructor(value) {
				this.value = value;
				this.left = null;
				this.right = null;
				this.depth = 0;
				this.xIndex = 0;
			}
		}

		const parseNumbers = (raw) => {
			if (!raw || !raw.trim()) {
				return { values: [], invalid: [] };
			}
			const tokens = raw
				.split(",")
				.map((part) => part.trim())
				.filter((part) => part.length > 0);
			const values = [];
			const invalid = [];
			tokens.forEach((token) => {
				const parsed = Number(token);
				if (Number.isFinite(parsed)) {
					values.push(parsed);
				} else {
					invalid.push(token);
				}
			});
			return { values, invalid };
		};

		const insertNode = (root, value) => {
			if (!root) {
				return new TreeNode(value);
			}
			if (value < root.value) {
				root.left = insertNode(root.left, value);
			} else {
				root.right = insertNode(root.right, value);
			}
			return root;
		};

		const buildBST = (values) => {
			let root = null;
			values.forEach((value) => {
				root = insertNode(root, value);
			});
			return root;
		};

		const toHierarchy = (node) => {
			if (!node) {
				return null;
			}
			const children = [];
			if (node.left) {
				children.push(toHierarchy(node.left));
			}
			if (node.right) {
				children.push(toHierarchy(node.right));
			}
			const data = { name: node.value.toString() };
			if (children.length) {
				data.children = children;
			}
			return data;
		};

		const assignAsciiPositions = (root) => {
			let counter = 0;
			let maxDepth = 0;
			const traverse = (node, depth) => {
				if (!node) {
					return;
				}
				if (depth > maxDepth) {
					maxDepth = depth;
				}
				traverse(node.left, depth + 1);
				node.xIndex = counter++;
				node.depth = depth;
				traverse(node.right, depth + 1);
			};
			traverse(root, 0);
			return { totalNodes: Math.max(counter, 1), maxDepth };
		};

		const buildAsciiPretty = (root) => {
			if (!root) {
				return [];
			}
			const { totalNodes, maxDepth } = assignAsciiPositions(root);
			const nodeStrings = [];
			const collectValues = (node) => {
				if (!node) {
					return;
				}
				nodeStrings.push(
					Number.isInteger(node.value)
						? node.value.toString()
						: node.value.toFixed(2)
				);
				collectValues(node.left);
				collectValues(node.right);
			};
			collectValues(root);
			const maxLen = Math.max(...nodeStrings.map((str) => str.length), 1);
			const colWidth = maxLen + 2;
			const rowsCount = maxDepth * 2 + 1;
			const cols = totalNodes;
			const rowLen = cols * colWidth;
			const rows = Array.from({ length: rowsCount }, () =>
				Array.from({ length: rowLen }, () => " ")
			);
			const placeString = (r, c, str) => {
				for (let i = 0; i < str.length; i += 1) {
					const idx = c + i;
					if (idx >= 0 && idx < rowLen) {
						rows[r][idx] = str[i];
					}
				}
			};
			const annotate = (node) => {
				if (!node) {
					return;
				}
				const row = node.depth * 2;
				const center =
					node.xIndex * colWidth + Math.floor(colWidth / 2);
				const valueString = Number.isInteger(node.value)
					? node.value.toString()
					: node.value.toFixed(2);
				const start = center - Math.floor(valueString.length / 2);
				placeString(row, start, valueString);
				const branchRow = row + 1;
				if (node.left) {
					const leftCenter =
						node.left.xIndex * colWidth + Math.floor(colWidth / 2);
					const mid = Math.floor((center + leftCenter) / 2);
					if (branchRow < rowsCount) {
						rows[branchRow][mid] = "/";
					}
				}
				if (node.right) {
					const rightCenter =
						node.right.xIndex * colWidth + Math.floor(colWidth / 2);
					const mid = Math.floor((center + rightCenter) / 2);
					if (branchRow < rowsCount) {
						rows[branchRow][mid] = "\\";
					}
				}
				annotate(node.left);
				annotate(node.right);
			};
			annotate(root);
			const output = rows.map((row) => row.join("").replace(/\s+$/g, ""));
			while (output.length && output[0].trim() === "") {
				output.shift();
			}
			while (output.length && output[output.length - 1].trim() === "") {
				output.pop();
			}
			return output;
		};

		const destroyPanZoom = () => {
			if (panZoomInstance) {
				panZoomInstance.destroy();
				panZoomInstance = null;
			}
		};

		const renderEmptyState = () => {
			destroyPanZoom();
			linksGroup.selectAll("*").remove();
			nodesGroup.selectAll("*").remove();
			svgElement.setAttribute("viewBox", "0 0 600 420");
			nodesGroup
				.append("text")
				.attr("x", 300)
				.attr("y", 190)
				.attr("text-anchor", "middle")
				.attr("fill", "rgba(148,163,184,0.8)")
				.attr("font-size", 18)
				.text("Nhập danh sách số và nhấn “Tạo cây” để bắt đầu");
			nodesGroup
				.append("text")
				.attr("x", 300)
				.attr("y", 225)
				.attr("text-anchor", "middle")
				.attr("fill", "rgba(148,163,184,0.6)")
				.attr("font-size", 16)
				.text("Sơ đồ trực quan sẽ xuất hiện tại đây");
		};

		const renderTree = (root) => {
			if (!root) {
				renderEmptyState();
				return;
			}
			const hierarchyData = toHierarchy(root);
			const rootHierarchy = d3.hierarchy(hierarchyData);
			const NODE_X_SPACING = 120;
			const NODE_Y_SPACING = 120;
			const treeLayout = d3
				.tree()
				.nodeSize([NODE_X_SPACING, NODE_Y_SPACING]);
			treeLayout(rootHierarchy);
			const nodes = rootHierarchy.descendants();
			const links = rootHierarchy.links();
			const xExtent = d3.extent(nodes, (node) => node.x);
			const yExtent = d3.extent(nodes, (node) => node.y);
			const marginX = 90;
			const marginY = 90;
			const width =
				(xExtent[1] - xExtent[0] || NODE_X_SPACING) + marginX * 2;
			const height =
				(yExtent[1] - yExtent[0] || NODE_Y_SPACING) + marginY * 2;
			nodes.forEach((node) => {
				node.x = node.x - xExtent[0] + marginX;
				node.y = node.y - yExtent[0] + marginY;
			});
			svgElement.setAttribute("viewBox", `0 0 ${width} ${height}`);
			linksGroup.selectAll("*").remove();
			nodesGroup.selectAll("*").remove();
			linksGroup
				.selectAll("line")
				.data(links)
				.join("line")
				.attr("x1", (link) => link.source.x)
				.attr("y1", (link) => link.source.y)
				.attr("x2", (link) => link.target.x)
				.attr("y2", (link) => link.target.y)
				.attr("stroke", "rgba(148,163,184,0.45)")
				.attr("stroke-width", 2)
				.attr("stroke-linecap", "round");
			const nodeGroups = nodesGroup
				.selectAll("g")
				.data(nodes)
				.join("g")
				.attr("transform", (node) => `translate(${node.x}, ${node.y})`);
			nodeGroups
				.append("circle")
				.attr("r", 28)
				.attr("fill", "#2563eb")
				.attr("stroke", "rgba(15,23,42,0.85)")
				.attr("stroke-width", 2.4);
			nodeGroups
				.append("text")
				.attr("text-anchor", "middle")
				.attr("dy", "0.35em")
				.attr("font-size", 14)
				.attr("font-weight", 600)
				.attr("fill", "#f8fafc")
				.text((node) =>
					node.data.name.length > 8
						? `${node.data.name.slice(0, 7)}…`
						: node.data.name
				);
			destroyPanZoom();
			panZoomInstance = svgPanZoom("#tree-svg", {
				panEnabled: true,
				zoomEnabled: true,
				controlIconsEnabled: false,
				fit: true,
				center: true,
				minZoom: 0.25,
				maxZoom: 8,
				zoomScaleSensitivity: 0.3,
			});
			requestAnimationFrame(() => {
				if (panZoomInstance) {
					panZoomInstance.fit();
					panZoomInstance.center();
				}
			});
		};

		const handleCopyAscii = async () => {
			if (!currentAscii) {
				return;
			}
			try {
				if (navigator.clipboard?.writeText) {
					await navigator.clipboard.writeText(currentAscii);
				} else {
					throw new Error("Clipboard API không hỗ trợ.");
				}
				setStatus("Đã copy ASCII vào clipboard.", "info");
			} catch (error) {
				console.warn(error);
				const tempArea = document.createElement("textarea");
				tempArea.value = currentAscii;
				tempArea.style.position = "fixed";
				tempArea.style.opacity = "0";
				document.body.appendChild(tempArea);
				tempArea.focus();
				tempArea.select();
				document.execCommand("copy");
				document.body.removeChild(tempArea);
				setStatus("Đã copy ASCII vào clipboard (fallback).", "info");
			}
		};

		const handleDownloadImage = async () => {
			if (!currentRoot) {
				return;
			}
			let Canvg;
			try {
				Canvg = await ensureCanvg();
			} catch (error) {
				console.error(error);
				setStatus(
					"Không thể tải thư viện xuất ảnh. Vui lòng kiểm tra kết nối mạng và thử lại.",
					"error"
				);
				return;
			}
			try {
				const serializer = new XMLSerializer();
				const clonedSvg = svgElement.cloneNode(true);
				const svgString = serializer.serializeToString(clonedSvg);
				const viewBox = svgElement.viewBox.baseVal;
				const width = viewBox?.width || svgElement.clientWidth || 800;
				const height =
					viewBox?.height || svgElement.clientHeight || 600;
				const scaleFactor = Math.min(3, window.devicePixelRatio || 1.5);
				const canvas = document.createElement("canvas");
				canvas.width = Math.max(1, Math.floor(width * scaleFactor));
				canvas.height = Math.max(1, Math.floor(height * scaleFactor));
				const ctx = canvas.getContext("2d");
				ctx.fillStyle =
					getComputedStyle(document.body).backgroundColor ||
					"#020617";
				ctx.fillRect(0, 0, canvas.width, canvas.height);
				const renderer = await Canvg.from(ctx, svgString, {
					enableRedraw: false,
				});
				await renderer.render();
				canvas.toBlob((blob) => {
					if (!blob) {
						setStatus("Không thể xuất PNG. Thử lại sau.", "error");
						return;
					}
					const downloadLink = document.createElement("a");
					downloadLink.href = URL.createObjectURL(blob);
					downloadLink.download = "binary-tree.png";
					document.body.appendChild(downloadLink);
					downloadLink.click();
					document.body.removeChild(downloadLink);
					setStatus("Đã tải ảnh PNG thành công.", "info");
				}, "image/png");
			} catch (error) {
				console.error(error);
				setStatus("Không thể tải ảnh PNG. Vui lòng thử lại.", "error");
			}
		};

		const handleGenerate = () => {
			const { values, invalid } = parseNumbers(numberInput.value);
			if (invalid.length) {
				setStatus(
					`Giá trị không hợp lệ: ${invalid.join(", ")}`,
					"error"
				);
				currentRoot = null;
				renderEmptyState();
				asciiPanel.classList.add("hidden");
				asciiEmpty.classList.remove("hidden");
				copyBtn.disabled = true;
				downloadBtn.disabled = true;
				currentAscii = "";
				return;
			}
			if (!values.length) {
				setStatus("Vui lòng nhập ít nhất một số.", "error");
				currentRoot = null;
				renderEmptyState();
				asciiPanel.classList.add("hidden");
				asciiEmpty.classList.remove("hidden");
				copyBtn.disabled = true;
				downloadBtn.disabled = true;
				currentAscii = "";
				return;
			}
			currentRoot = buildBST(values);
			renderTree(currentRoot);
			const asciiLines = buildAsciiPretty(currentRoot);
			currentAscii = asciiLines.join("\n");
			asciiText.textContent = currentAscii;
			asciiPanel.classList.remove("hidden");
			asciiEmpty.classList.add("hidden");
			copyBtn.disabled = false;
			downloadBtn.disabled = false;
			setStatus(`Đã xây dựng cây với ${values.length} nút.`, "info");
		};

		const handleSample = () => {
			const sample = "50, 145, 150, 130, 120, 140, 30, 70, 75, 80, 35";
			numberInput.value = sample;
			handleGenerate();
		};

		copyBtn.addEventListener("click", handleCopyAscii);
		downloadBtn.addEventListener("click", handleDownloadImage);
		generateBtn.addEventListener("click", handleGenerate);
		sampleBtn.addEventListener("click", handleSample);
		numberInput.addEventListener("keydown", (event) => {
			if (event.key === "Enter") {
				event.preventDefault();
				handleGenerate();
			}
		});
		zoomInBtn.addEventListener("click", () => {
			if (panZoomInstance) {
				panZoomInstance.zoomIn();
			}
		});
		zoomOutBtn.addEventListener("click", () => {
			if (panZoomInstance) {
				panZoomInstance.zoomOut();
			}
		});
		resetViewBtn.addEventListener("click", () => {
			if (panZoomInstance) {
				panZoomInstance.resetZoom();
				panZoomInstance.center();
			}
		});
		renderEmptyState();
		setStatus("Sẵn sàng. Nhập danh sách số và nhấn Tạo cây để bắt đầu.");
	};

	document.addEventListener("DOMContentLoaded", () => {
		init().catch((error) => {
			console.error("Lỗi khởi tạo visualizer:", error);
		});
	});
})();
